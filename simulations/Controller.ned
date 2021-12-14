simple Controller {
    parameters:
        volatile double messageLength = uniform(100, 1000);
        volatile double sendInterval = uniform(0.1, 1);
        volatile double duration = uniform(10, 100);
                
    gates:
        input in;
        output out;
}