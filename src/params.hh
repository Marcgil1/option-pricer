#pragma once

#define NUM_TRIALS    (   int(10000))
#define INITIAL_VALUE (double(5.0))
#define STRIKE_PRICE  (double(10.0))
#define NUM_STEPS     (   int(1000))
#define TOTAL_TIME    (double(1.0))
#define STEP_SIZE     (double(TOTAL_TIME / NUM_STEPS))
#define ALPHA         (double(0.06))
#define BETA          (double(0.3))
#define RETURN_RATE   (double(0.06))