simple Controller {
    parameters:
        volatile double messageLength = 500;
        volatile double sendInterval = 0.1;
        volatile double duration = 10;
                
    gates:
        input in;
        output out;
}