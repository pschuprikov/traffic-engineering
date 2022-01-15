import Controller;

import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.node.inet.StandardHost;
import inet.node.inet.Router;
import ned.DatarateChannel;


network FatTreeNetwork
{
    types:
        channel ServerEthernet extends DatarateChannel
        {
            delay = uniform(5us, 10us);
            datarate = 10Mbps;
        }

        channel SwitchEthernet extends DatarateChannel
        {
            delay = uniform(2us, 3us);
            datarate = 10Mbps;
        }

    submodules:
        router_2_2: Router {
            parameters:
                multicastForwarding = true;
                @display("p=196,276,x");
        }

        server1: StandardHost {
            parameters:
                multicastForwarding = true;
                @display("p=58,450,x");
        }

        server2: StandardHost {
            parameters:
                multicastForwarding = true;
                @display("p=112,450,x");
        }

        router_3_1: Router {
            parameters:
                multicastForwarding = true;
                @display("p=97,360,x");
        }

        server3: StandardHost {
            parameters:
                multicastForwarding = true;
                @display("p=170,450,x");
        }

        server4: StandardHost {
            parameters:
                multicastForwarding = true;
                @display("p=226,450,x");
        }

        router_3_2: Router {
            parameters:
                multicastForwarding = true;
                @display("p=196,360,x");
        }

        server5: StandardHost {
            parameters:
                multicastForwarding = true;
                @display("p=340,450,x");
        }

        server6: StandardHost {
            parameters:
                multicastForwarding = true;
                @display("p=395,450,x");
        }

        router_3_3: Router {
            parameters:
                multicastForwarding = true;
                @display("p=395,360,x");
        }

        server7: StandardHost {
            parameters:
                multicastForwarding = true;
                @display("p=456,450,x");
        }

        server8: StandardHost {
            parameters:
                multicastForwarding = true;
                @display("p=514,450,x");
        }

        router_3_4: Router {
            parameters:
                multicastForwarding = true;
                @display("p=482,360,x");
        }

        router_2_1: Router {
            parameters:
                multicastForwarding = true;
                @display("p=97,276,x");
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
        
        router_2_3: Router {
            parameters:
            	multicastForwarding = true;
            	@display("p=395,276");
        }
        
        router_2_4: Router {
            parameters:
            	multicastForwarding = true;
            	@display("p=482,276");
        }
        
        router_2_5: Router {
            parameters:
                multicastForwarding = true;
                @display("p=650,276,x");
        }

        router_2_6: Router {
            parameters:
                multicastForwarding = true;
                @display("p=755,276,x");
        }

        router_3_5: Router {
            parameters:
                multicastForwarding = true;
                @display("p=650,360,x");
        }

        router_3_6: Router {
            parameters:
                multicastForwarding = true;
                @display("p=755,360,x");
        }

        server9: StandardHost {
            parameters:
                multicastForwarding = true;
                @display("p=611,450,x");
        }

        server10: StandardHost {
            parameters:
                multicastForwarding = true;
                @display("p=671,450,x");
        }

        server11: StandardHost {
            parameters:
                multicastForwarding = true;
                @display("p=731,450,x");
        }

        server12: StandardHost {
            parameters:
                multicastForwarding = true;
                @display("p=787,450,x");
        }

        router_2_7: Router {
            parameters:
                multicastForwarding = true;
                @display("p=929,276,x");
        }

        router_2_8: Router {
            parameters:
                multicastForwarding = true;
                @display("p=1043,276,x");
        }

        router_3_7: Router {
            parameters:
                multicastForwarding = true;
                @display("p=929,360,x");
        }

        router_3_8: Router {
            parameters:
                multicastForwarding = true;
                @display("p=1043,360,x");
        }

        server13: StandardHost {
            parameters:
                multicastForwarding = true;
                @display("p=906,450,x");
        }

        server14: StandardHost {
            parameters:
                multicastForwarding = true;
                @display("p=968,450,x");
        }

        server15: StandardHost {
            parameters:
                multicastForwarding = true;
                @display("p=1026,450,x");
        }

        server16: StandardHost {
            parameters:
                multicastForwarding = true;
                @display("p=1082,450,x");
        }

        router_1_1: Router {
            parameters:
            	multicastForwarding = true;
            	@display("p=313,119");
        }
        router_1_2: Router {
            parameters:
            	multicastForwarding = true;
            	@display("p=521,119");
        }
        router_1_3: Router {
            parameters:
                multicastForwarding = true;
            	@display("p=731,119");
        }
        router_1_4: Router {
            parameters:
            	multicastForwarding = true;
            	@display("p=929,119");
        }
    connections:
        tic.out --> {  delay = 10ms; } --> tac.in;
        tic.in <-- {  delay = 10ms; } <-- tac.out;

        router_3_1.ethg++ <--> ServerEthernet <--> server1.ethg++;
        router_3_1.ethg++ <--> ServerEthernet <--> server2.ethg++;
        router_3_2.ethg++ <--> ServerEthernet <--> server3.ethg++;
        router_3_2.ethg++ <--> ServerEthernet <--> server4.ethg++;
        router_3_3.ethg++ <--> ServerEthernet <--> server5.ethg++;
        router_3_3.ethg++ <--> ServerEthernet <--> server6.ethg++;
        router_3_4.ethg++ <--> ServerEthernet <--> server7.ethg++;
        router_3_4.ethg++ <--> ServerEthernet <--> server8.ethg++;
        router_2_1.ethg++ <--> SwitchEthernet <--> router_3_2.ethg++;
        router_2_2.ethg++ <--> SwitchEthernet <--> router_3_1.ethg++;
        router_2_2.ethg++ <--> SwitchEthernet <--> router_3_2.ethg++;
        router_2_1.ethg++ <--> SwitchEthernet <--> router_3_1.ethg++;
        router_3_3.ethg++ <--> SwitchEthernet <--> router_2_3.ethg++;
        router_3_3.ethg++ <--> SwitchEthernet <--> router_2_4.ethg++;
        router_3_4.ethg++ <--> SwitchEthernet <--> router_2_3.ethg++;
        router_3_4.ethg++ <--> SwitchEthernet <--> router_2_4.ethg++;
        router_2_6.ethg++ <--> SwitchEthernet <--> router_3_5.ethg++;
        router_2_6.ethg++ <--> SwitchEthernet <--> router_3_6.ethg++;
        router_3_5.ethg++ <--> ServerEthernet <--> server9.ethg++;
        router_3_5.ethg++ <--> ServerEthernet <--> server10.ethg++;
        router_2_5.ethg++ <--> SwitchEthernet <--> router_3_5.ethg++;
        router_2_5.ethg++ <--> SwitchEthernet <--> router_3_6.ethg++;
        router_2_5.ethg++ <--> SwitchEthernet <--> router_3_5.ethg++;
        router_3_6.ethg++ <--> ServerEthernet <--> server11.ethg++;
        router_3_6.ethg++ <--> ServerEthernet <--> server12.ethg++;
        router_2_8.ethg++ <--> SwitchEthernet <--> router_3_7.ethg++;
        router_2_8.ethg++ <--> SwitchEthernet <--> router_3_8.ethg++;
        router_3_7.ethg++ <--> ServerEthernet <--> server13.ethg++;
        router_3_7.ethg++ <--> ServerEthernet <--> server14.ethg++;
        router_2_7.ethg++ <--> SwitchEthernet <--> router_3_7.ethg++;
        router_2_7.ethg++ <--> SwitchEthernet <--> router_3_8.ethg++;
        router_2_7.ethg++ <--> SwitchEthernet <--> router_3_7.ethg++;
        router_3_8.ethg++ <--> ServerEthernet <--> server15.ethg++;
        router_3_8.ethg++ <--> ServerEthernet <--> server16.ethg++;
        router_2_1.ethg++ <--> SwitchEthernet <--> router_1_1.ethg++;
        router_2_3.ethg++ <--> SwitchEthernet <--> router_1_1.ethg++;
        router_2_5.ethg++ <--> SwitchEthernet <--> router_1_1.ethg++;
        router_2_7.ethg++ <--> SwitchEthernet <--> router_1_1.ethg++;
        router_2_1.ethg++ <--> SwitchEthernet <--> router_1_2.ethg++;
        router_2_3.ethg++ <--> SwitchEthernet <--> router_1_2.ethg++;
        router_2_5.ethg++ <--> SwitchEthernet <--> router_1_2.ethg++;
        router_2_7.ethg++ <--> SwitchEthernet <--> router_1_2.ethg++;
        router_2_2.ethg++ <--> SwitchEthernet <--> router_1_3.ethg++;
        router_2_2.ethg++ <--> SwitchEthernet <--> router_1_4.ethg++;
        router_2_4.ethg++ <--> SwitchEthernet <--> router_1_3.ethg++;
        router_2_4.ethg++ <--> SwitchEthernet <--> router_1_4.ethg++;
        router_2_6.ethg++ <--> SwitchEthernet <--> router_1_3.ethg++;
        router_2_6.ethg++ <--> SwitchEthernet <--> router_1_4.ethg++;
        router_2_8.ethg++ <--> SwitchEthernet <--> router_1_4.ethg++;
        router_2_8.ethg++ <--> SwitchEthernet <--> router_1_3.ethg++;
}
