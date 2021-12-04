import Controller;

import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.node.inet.StandardHost;
import inet.node.inet.Router;
import ned.DatarateChannel;


network FatTreeNetwork
{
    types:
        channel ethernet extends DatarateChannel
        {
            delay = uniform(0.00015s, 0.00005s);
            datarate = 10Mbps;
        }

    submodules:
        router2: Router {
            parameters:
                multicastForwarding = true;
                @display("p=839,50,x");
        }

        server1: StandardHost {
            parameters:
                multicastForwarding = true;
                @display("p=50,450,x");
        }

        server2: StandardHost {
            parameters:
                multicastForwarding = true;
                @display("p=175,450,x");
        }

        router3: Router {
            parameters:
                multicastForwarding = true;
                @display("p=112,250,x");
        }

        server3: StandardHost {
            parameters:
                multicastForwarding = true;
                @display("p=300,450,x");
        }

        server4: StandardHost {
            parameters:
                multicastForwarding = true;
                @display("p=425,450,x");
        }

        router4: Router {
            parameters:
                multicastForwarding = true;
                @display("p=362,250,x");
        }

        server5: StandardHost {
            parameters:
                multicastForwarding = true;
                @display("p=550,450,x");
        }

        server6: StandardHost {
            parameters:
                multicastForwarding = true;
                @display("p=675,450,x");
        }

        router5: Router {
            parameters:
                multicastForwarding = true;
                @display("p=612,250,x");
        }

        server7: StandardHost {
            parameters:
                multicastForwarding = true;
                @display("p=800,450,x");
        }

        server8: StandardHost {
            parameters:
                multicastForwarding = true;
                @display("p=925,450,x");
        }

        router6: Router {
            parameters:
                multicastForwarding = true;
                @display("p=862,250,x");
        }

        router1: Router {
            parameters:
                multicastForwarding = true;
                @display("p=341,50,x");
        }

        configurator: Ipv4NetworkConfigurator {
            @display("p=50,46");
        }

        tic: Controller {
            @display("p=45,128");
        }
        tac: Controller {
            @display("p=187,87");
        }
    connections:
        router3.ethg++ <--> ethernet <--> server1.ethg++;
        router3.ethg++ <--> ethernet <--> server2.ethg++;
        router4.ethg++ <--> ethernet <--> server3.ethg++;
        router4.ethg++ <--> ethernet <--> server4.ethg++;
        router5.ethg++ <--> ethernet <--> server5.ethg++;
        router5.ethg++ <--> ethernet <--> server6.ethg++;
        router6.ethg++ <--> ethernet <--> server7.ethg++;
        router6.ethg++ <--> ethernet <--> server8.ethg++;
        router1.ethg++ <--> ethernet <--> router3.ethg++;
        router1.ethg++ <--> ethernet <--> router4.ethg++;
        router1.ethg++ <--> ethernet <--> router5.ethg++;
        router1.ethg++ <--> ethernet <--> router6.ethg++;
        router2.ethg++ <--> ethernet <--> router3.ethg++;
        router2.ethg++ <--> ethernet <--> router4.ethg++;
        router2.ethg++ <--> ethernet <--> router5.ethg++;
        router2.ethg++ <--> ethernet <--> router6.ethg++;

        tic.out --> {  delay = 100ms; } --> tac.in;
        tic.in <-- {  delay = 100ms; } <-- tac.out;
}
