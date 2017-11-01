
// basic parameters
int transducers[] = {12,14,19};
int NUM_INPUTS = sizeof(transducers) / sizeof(int);
float THRESHOLD[NUM_INPUTS] = {1023};
float K = 1.5;
int PEAK_SAMPS = 0;
int FILTER = 3;

// peak vars
int IN_PEAK[NUM_INPUTS] = {0};
long PEAK_CNT[NUM_INPUTS] = {0};
long PEAK_SUM[NUM_INPUTS] = {0};
int PEAK_MAX[NUM_INPUTS] = {0}

// noise vars
long NOISE_CNT[NUM_INPUTS] = {0};
long NOISE_SUM[NUM_INPUTS] = {0};
long NOISE_SQUARES[NUM_INPUTS] = {0};

// transmit a peak to the serial connection
void send_peak(int i, int voltage){
    ;
}

// helper function for noise maintenance
void update_noise(int i, int voltage){
    NOISE_CNT[i]++;
    NOISE_SUM[i] += voltage;
    NOISE_SQUARES[i] += sq((long)voltage);
    // threshold will always approach K standard deviations from mean
    THRESHOLD[i] = (THESHOLD[i] + K*sqrt(NOISE_SQUARES[i] - NOISE_SUM[i])/NOISE_CNT[i])/2;
}

// peak quantification
void update_peak(int i, int voltage){
    PEAK_CNT[i]++;
    PEAK_SUM[i] += voltage;
    // set absolute max
    if (voltage > PEAK_MAX[i]){
        PEAK_MAX[i] = voltage;
    }
    else if(PEAK_CNT >= FILTER && voltage < (PEAK_SUM/PEAK_CNT)){
        send_peak(i, PEAK_MAX[i]);
        PEAK_CNT[i] = 0;
        PEAK_SUM[i] = 0;
        PEAK_MAX[i] = 0;
        IN_PEAK[i] = 0;
    }
}

// setup
void setup{
    for(int i = 0; i < NUM_INPUTS; i++){
        pinMode(transducers[i], INPUT);
    }
}

// main loop
void main {
    while(True){
        int voltage[NUM_INPUTS];
        // Read first for sake of syncing inputs as best as possible
        for (i = 0; i < NUM_INPUTS; i++){
            voltage[i] = analogRead(transducers[i]);
        }
        for (i = 0; i < NUM_INPUTS; i++){
            // update noise if not in peak
            if(!IN_PEAK[i]){
                if voltage[i] > THRESHOLD[i]{
                    IN_PEAK[i] = 1;
                }
                else {
                    update_noise(i, voltage[i])
                    continue;
                }
            }
            update_peak(i, voltage[i]);
        }
    }
}