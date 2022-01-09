from typing import Dict, List


class Event:
    def __init__(self, event_line: str):
        node, packet, time = event_line.split()
        _, tunnel_index, iteration_index = packet.split('-')
        self.node = node
        self.tunnel_index = tunnel_index
        self.iteration_index = iteration_index
        self.time = time


class Iteration:
    def __init__(self, tunnel_index: int, iteration_index: int):
        self.tunnel_index: int = tunnel_index
        self.iteration_index: int = iteration_index
        self.time_control: Dict[str, float] = {}

    def add_event(self, event: Event):
        if event.node in self.time_control:
            raise Exception('the specified node already used')
        self.time_control[event.node] = event.time

    def get_delays(self, sender: str, receivers: List[str]) -> (float, float):
        min_time = float('inf')
        max_time = 0.0
        for receiver in receivers:
            self.__check_presence(receiver)
            min_time = min(min_time, self.time_control[receiver])
            max_time = max(max_time, self.time_control[receiver])
        self.__check_presence(sender)
        return min_time - self.time_control[sender], max_time - self.time_control[sender]

    def __check_presence(self, node: str):
        if node in self.time_control:
            raise Exception(f'the node({node}) have not got '
                            f'in the tunnel#{self.tunnel_index} '
                            f'on iteration#{self.iteration_index}')


class Tunnel:
    def __init__(self, index: int):
        self.index = index
        self.iterations: Dict[int, Iteration] = {}

    def add_event(self, event: Event):
        if not event.iteration_index in self.iterations:
            self.iterations[event.iteration_index] = Iteration(event.iteration_index, event.tunnel_index)
        iteration = self.iterations[event.iteration_index]
        iteration.add_event(event)

    def get_delays(self, sender: str, receivers: List[str]) -> (float, float):
        min_delay = float('inf')
        max_delay = 0.0
        for iteration in self.iterations.values():
            current_min_delay, current_max_delay = iteration.get_delays(sender, receivers)
            min_delay = min(min_delay, current_min_delay)
            max_delay = max(max_delay, current_max_delay)
        return min_delay, max_delay


class Experiment:
    def __init__(self):
        self.tunnels: Dict[int, Tunnel] = {}

    def add_event(self, event: Event):
        if not event.tunnel_index in self.tunnels:
            self.tunnels[event.tunnel_index] = Tunnel(event.tunnel_index)
        tunnel = self.tunnels[event.tunnel_index]
        tunnel.add_event(event)


def compute(filename: str):
    experiment = Experiment()
    with open(filename) as file:
        for line in file:
            event = Event(line)
            experiment.add_event(event)


if __name__ == '__main__':
    compute('venv/log.txt')
