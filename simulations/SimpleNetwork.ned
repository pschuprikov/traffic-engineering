import Controller;

import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.node.inet.Router;
import inet.node.inet.StandardHost;
import ned.DatarateChannel;

network SimpleNetwork
{
    types:
        channel ethernet extends DatarateChannel
        {
            delay = normal(0.00015s, 0.00005s);
            datarate = 10Mbps;
        }

    submodules:
        server: StandardHost {
            parameters:
                multicastForwarding = true;
                @display("p=84,217;i=device/pc2");
            gates:
                ethg[1];
        }
        client1: StandardHost {
            parameters:
                multicastForwarding = true;
                @display("p=383,131;i=device/pc2");
            gates:
                ethg[1];
        }
        client2: StandardHost {
            parameters:
                multicastForwarding = true;
                @display("p=383,217;i=device/pc2");
            gates:
                ethg[1];
        }
        client3: StandardHost {
            parameters:
                multicastForwarding = true;
                @display("p=375,306;i=device/pc2");
            gates:
                ethg[1];
        }
        router: Router {
            parameters:
                multicastForwarding = true;
                @display("p=222,217");
            gates:
                ethg[4];
        }
        configurator: Ipv4NetworkConfigurator {
            @display("p=324,54;is=s");
        }

        tic: Controller {
            @display("p=45,128");
        }
        tac: Controller {
            @display("p=187,87");
        }
    connections:
        server.ethg[0] <--> ethernet <--> router.ethg[0];

        router.ethg[1] <--> ethernet <--> client1.ethg[0];
        router.ethg[2] <--> ethernet <--> client2.ethg[0];
        router.ethg[3] <--> ethernet <--> client3.ethg[0];

        tic.out --> {  delay = 100ms; } --> tac.in;
        tic.in <-- {  delay = 100ms; } <-- tac.out;
}
