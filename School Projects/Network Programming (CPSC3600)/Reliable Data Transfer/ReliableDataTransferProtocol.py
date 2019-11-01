from Simulator import Simulator
from Simulator import Packet
from Simulator import EventEntity
from collections import OrderedDict
from enum import Enum


class ReliableDataTransferProtocol():
    def __init__(self, bidirectional = False):
        self.bidirectional = bidirectional
        self.simulator = None
        self.seqnum_a = 0
        self.acknum_a = 0
        self.seqnum_b = 0
        self.acknum_b = 0
        self.pktlst_a = OrderedDict()


    # This routine will be called once, before any of your other A-side routines are called.
    # It can be used to do any required initialization.
    def A_Init(self):
        pass

    def checksum(self, message, seqnum, acknum):
        sum = 0
        for c in message:
            sum += ord(c)

        sum += seqnum
        sum += acknum

        sum = -(sum % 256)
        return sum

    # This routine will be called whenever the upper layer at the sending side (A) has a message to send.
    # It is the job of your protocol to insure that the data in such a message is delivered in-order,
    # and correctly, to the receiving side upper layer.
    def A_CommunicateWithApplicationLayer(self, message):
        self.simulator.trace("A received {} from application layer".format(message),1)
        
        sum = 0

        pktA = Packet()
        pktA.acknum = self.acknum_a
        pktA.seqnum = self.seqnum_a
        pktA.payload = message
        
        pktA.checksum = self.checksum(message, pktA.seqnum, pktA.acknum)

        self.seqnum_a += 1
        self.pktlst_a[pktA.seqnum] = pktA

        self.simulator.to_layer3(EventEntity.A, pktA)
        self.simulator.start_timer(EventEntity.A, 50.0)
        

    # This routine will be called whenever a packet sent from the B-side (i.e., as a result of a tolayer3()
    # being done by a B-side procedure) arrives at the A-side. packet is the (possibly corrupted) packet
    # sent from the B-side.
    def A_CommunicateWithNetworkLayer(self, packet):
        self.simulator.trace("A received a packet (SEQ: {}, ACK: {}, Checksum: {}, Payload: {}) from network layer layer".format(
            packet.seqnum, packet.acknum, packet.checksum, packet.payload), 1)

        if packet.checksum == self.checksum(packet.payload, packet.seqnum, packet.acknum):
            if packet.acknum == self.pktlst_a[packet.seqnum].acknum:
                pass
            elif packet.seqnum != self.pktlst_a[packet.seqnum].seqnum:
                pass
            else:
                self.simulator.stop_timer(EventEntity.A)
                self.pktlst_a.pop(packet.seqnum)
                pass
        

    # This routine will be called when A's timer expires (thus generating a timer interrupt). You'll probably
    # want to use this routine to control the retransmission of packets. See starttimer() and stoptimer()
    # below for how the timer is started and stopped.
    def A_TimerInterrupt(self):
        self.simulator.trace("A experienced a timer interrupt", 1)
        
        pkt_send = next(iter(self.pktlst_a.items())) # pkt_send will be used to resend the first entry in the ordered list

        self.simulator.to_layer3(EventEntity.A, pkt_send[1]) 
        self.simulator.start_timer(EventEntity.A, 50.0)
        
    # This routine will be called once, before any of your other B-side routines are called.
    # It can be used to do any required initialization.
    def B_Init(self):
        pass


    # This routine will be called whenever a packet sent from the A-side (i.e., as a result of a tolayer3() being done
    # by a A-side procedure) arrives at the B-side. packet is the (possibly corrupted) packet sent from the A-side.
    def B_CommunicateWithNetworkLayer(self, packet):
        self.simulator.trace("B received a packet (SEQ: {}, ACK: {}, Checksum: {}, Payload: {}) from network layer layer".format(
            packet.seqnum, packet.acknum, packet.checksum, packet.payload), 1)
        
        ack = True # true represents an ACK, false represents a NACK

        pktB = Packet()
        
        if packet.checksum == self.checksum(packet.payload, packet.seqnum, packet.acknum):
            pktB.acknum = packet.acknum + 1
        else:
            pktB.acknum = packet.acknum
            ack = False
     
        pktB.seqnum = packet.seqnum
        pktB.checksum = self.checksum(pktB.payload, pktB.seqnum, pktB.acknum)
        self.simulator.to_layer3(EventEntity.B, pktB)
        
        if packet.seqnum == self.seqnum_b and ack:
            self.simulator.to_layer5(1, packet.payload)
            self.seqnum_b += 1
            

if __name__ == "__main__":
    rdt = ReliableDataTransferProtocol()
    simulator = Simulator(rdt)

    simulator.Setup()
    simulator.Simulate()