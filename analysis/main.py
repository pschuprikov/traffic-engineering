from typing import Dict, List, NamedTuple

import numpy as np
import matplotlib.pyplot as plt


def show_distribution(array: List[float]):
    count, bins, _ = plt.hist(array, 15, density=True, range=(0, 1))
    plt.plot(bins, np.ones_like(bins))
    plt.show()


class Event:
    def __init__(self, event_line: str):
        node, packet, time = event_line.split()
        _, tunnel_index, iteration_index = packet.split('-')
        self.node = node
        self.tunnel_index = int(tunnel_index)
        self.iteration_index = int(iteration_index)
        self.time = float(time)


class Iteration:
    def __init__(self, iteration_index: int, tunnel_index: int):
        self.tunnel_index: int = tunnel_index
        self.iteration_index: int = iteration_index
        self.time_control: Dict[str, float] = {}

    def add_event(self, event: Event):
        if event.node in self.time_control:
            raise Exception('the specified node already used')
        self.time_control[event.node] = event.time

    def get_latencies(self, sender: str, receivers: List[str]) -> (float, float):
        min_time = float('inf')
        max_time = 0.0
        for receiver in receivers:
            self.__check_presence(receiver)
            min_time = min(min_time, self.time_control[receiver])
            max_time = max(max_time, self.time_control[receiver])
        self.__check_presence(sender)
        return min_time - self.time_control[sender], max_time - self.time_control[sender]

    def __check_presence(self, node: str):
        if not node in self.time_control:
            raise Exception(f'the node({node}) have not got '
                            f'in the tunnel#{self.tunnel_index} '
                            f'on iteration#{self.iteration_index}')


class Tunnel:
    def __init__(self, index: int):
        self.index = index
        self.iterations: Dict[int, Iteration] = {}
        self.min_latency: float = None
        self.max_latency: float = None

    def add_event(self, event: Event):
        if not event.iteration_index in self.iterations:
            self.iterations[event.iteration_index] = Iteration(event.iteration_index, event.tunnel_index)
        iteration = self.iterations[event.iteration_index]
        iteration.add_event(event)

    def get_latencies(self, sender: str, receivers: List[str]) -> (float, float):
        min_latency = float('inf')
        max_latency = 0.0
        for iteration in self.iterations.values():
            try:
                current_min_latency, current_max_latency = iteration.get_latencies(sender, receivers)
                min_latency = min(min_latency, current_min_latency)
                max_latency = max(max_latency, current_max_latency)
            except Exception as exception:
                pass
        return min_latency, max_latency

    def set_latencies(self, min_latency: float, max_latency: float):
        self.min_latency = min_latency
        self.max_latency = max_latency

    def get_distributions(self, sender: str, receivers: List[str]) -> (List[float], List[float]):
        if self.min_latency is None or self.max_latency is None:
            raise Exception("the latencies was not initialized")
        min_distribution = list()
        max_distribution = list()
        for iteration in self.iterations.values():
            try:
                current_min_latency, current_max_latency = iteration.get_latencies(sender, receivers)
                min_distribution.append((current_min_latency - self.min_latency) / (self.max_latency - self.min_latency))
                max_distribution.append((current_max_latency - self.min_latency) / (self.max_latency - self.min_latency))
            except Exception as exception:
                print(exception)
                pass
        return min_distribution, max_distribution


class TunnelDescription:
    def __init__(self, sender: str, receivers: List[str]):
        self.sender: str = sender
        self.receivers: List[str] = receivers


class TunnelDescription(NamedTuple):
    sender: str 
    receivers: List[str]


def get_tunnel_descriptions(filename: str) -> List[TunnelDescription]:
    result = []
    with open(filename) as file:
        for line in file:
            nodes = line.split()
            result.append(TunnelDescription(nodes[0], nodes[1:]))
    return result


class Experiment:
    def __init__(self):
        self.tunnels: Dict[int, Tunnel] = {}

    def add_event(self, event: Event):
        if not event.tunnel_index in self.tunnels:
            self.tunnels[event.tunnel_index] = Tunnel(event.tunnel_index)
        tunnel = self.tunnels[event.tunnel_index]
        tunnel.add_event(event)

    def print_statistics(self, tunnel_descriptions: List[TunnelDescription]):
        for index, description in enumerate(tunnel_descriptions):
            if not index in self.tunnels:
                continue
            tunnel = self.tunnels[index]
            min_latency, max_latency = tunnel.get_latencies(description.sender, description.receivers)
            print(f'Tunnel#{index}, min_latency: {min_latency}, max_latency: {max_latency}')

    def set_adjustment_latencies(self, filename: str):
        with open(filename) as file:
            for index, line in enumerate(file):
                if not index in self.tunnels:
                    continue
                tunnel = self.tunnels[index]
                latencies = list(map(float, line.split()))
                min_latency, max_latency = latencies[0], latencies[1]
                tunnel.set_latencies(min_latency, max_latency)

    def get_distributions(self, tunnel_descriptions: List[TunnelDescription]) -> (List[float], List[float]):
        min_distribution = list()
        max_distribution = list()
        for index, description in enumerate(tunnel_descriptions):
            if not index in self.tunnels:
                continue
            tunnel = self.tunnels[index]
            current_min_distribution, current_max_distribution = tunnel.get_distributions(description.sender,
                                                                                          description.receivers)
            min_distribution += current_min_distribution
            max_distribution += current_max_distribution
        return min_distribution, max_distribution


def get_experiment(filename: str) -> Experiment:
    result = Experiment()
    with open(filename) as file:
        for line in file:
            if len(line.split()) != 3:
                continue
            event = Event(line)
            result.add_event(event)
    return result


def main():
    experiment = get_experiment('../simulations/results/events.log')
    experiment.set_adjustment_latencies('../simulations/results/adjustment.log')
    descriptions = get_tunnel_descriptions('../simulations/results/tunnel_descriptions.log')
    min_distribution, max_distribution = experiment.get_distributions(descriptions)
    # print(min_distribution)
    # print(max_distribution)
    show_distribution(min_distribution)
    show_distribution(max_distribution)
    experiment.print_statistics(descriptions)


if __name__ == '__main__':
    main()
