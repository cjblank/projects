from Simulator import Simulator
from Simulator import Packet
from Simulator import EventEntity
from enum import Enum


class GBN():
    def __init__(self, bidirectional = False):
        self.bidirectional = bidirectional
        self.simulator = None


    # This routine will be called once, before any of your other A-side routines are called.
    # It can be used to do any required initialization.
    def A_Init(self):
        pass


    # This routine will be called whenever the upper layer at the sending side (A) has a message to send.
    # It is the job of your protocol to insure that the data in such a message is delivered in-order,
    # and correctly, to the receiving side upper layer.
    def A_CommunicateWithApplicationLayer(self, message):
        self.simulator.trace("A received {} from application layer".format(message),1)


    # This routine will be called whenever a packet sent from the B-side (i.e., as a result of a tolayer3()
    # being done by a B-side procedure) arrives at the A-side. packet is the (possibly corrupted) packet
    # sent from the B-side.
    def A_CommunicateWithNetworkLayer(self, packet):
        self.simulator.trace("A received a packet (SEQ: {}, ACK: {}, Checksum: {}, Payload: {}) from network layer layer".format(
            packet.seqnum, packet.acknum, packet.checksum, packet.payload), 1)


    # This routine will be called when A's timer expires (thus generating a timer interrupt). You'll probably
    # want to use this routine to control the retransmission of packets. See starttimer() and stoptimer()
    # below for how the timer is started and stopped.
    def A_TimerInterrupt(self):
        self.simulator.trace("A experienced a timer interrupt", 1)


    # This routine will be called once, before any of your other B-side routines are called.
    # It can be used to do any required initialization.
    def B_Init(self):
        pass


    # This routine will be called whenever a packet sent from the A-side (i.e., as a result of a tolayer3() being done
    # by a A-side procedure) arrives at the B-side. packet is the (possibly corrupted) packet sent from the A-side.
    def B_CommunicateWithNetworkLayer(self, packet):
        self.simulator.trace("B received a packet (SEQ: {}, ACK: {}, Checksum: {}, Payload: {}) from network layer layer".format(
            packet.seqnum, packet.acknum, packet.checksum, packet.payload), 1)



if __name__ == "__main__":
    rdt = GBN()
    simulator = Simulator(rdt)

    simulator.Setup()
    simulator.Simulate()