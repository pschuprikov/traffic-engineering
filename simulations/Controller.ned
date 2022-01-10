simple Controller {
    parameters:
        volatile double messageLength = 500;
        volatile double sendInterval = uniform(0.1, 1);
        volatile double duration = uniform(10, 100);
                
    gates:
        input in;
        output out;
}