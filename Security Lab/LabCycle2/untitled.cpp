#include<bits/stdc++.h>
#include<gmpxx.h>
using namespace std;

#define ll long long
#define MAXN 70000000
#define pb push_back

int main(int argc, char const *argv[])
{
	CommandLine cmd;
	cmd.Parse (argc, argv);
	Time::SetResolution (Time::NS);

	NodeContainer nodes;
	nodes.Create (3);

	PointToPointHelper pointToPoint;
	pointToPoint.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
	pointToPoint.SetChannelAttribute ("Delay", StringValue ("2ms"));

	NetDeviceContainer p2pDevices;
	p2pDevices = pointToPoint.Install (nodes.Get(0),nodes.Get(1));

	InternetStackHelper stack;
  	stack.Install (nodes);

  	Ipv4AddressHelper address;
  	address.SetBase ("10.1.2.0", "255.255.255.0");
  	Ipv4InterfaceContainer interfaces = address.Assign (p2pDevices);

  	Ipv4GlobalRoutingHelper:: PopulateRoutingTables();

  	Ptr<Socket> srcSocket = Socket::CreateSocket (nodes.Get(0), TypeId::LookupByName ("ns3::UdpSocketFactory"));
  	srcSocket->Bind ();

  	Ptr<Socket> dstSocket = Socket::CreateSocket (nodes.Get(1), TypeId::LookupByName ("ns3::UdpSocketFactory"));
  	uint16_t dstport = 12345;
  	Ipv4Address dstaddr ("10.0.0.2");
  	InetSocketAddress dst = InetSocketAddress (dstaddr, dstport);
  	dstSocket->Bind (dst);
  	dstSocket->SetRecvCallback (MakeCallback (&dstSocketRecv));
	return 0;
}