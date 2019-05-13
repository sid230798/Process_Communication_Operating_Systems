/*

	Name :- Siddharth Nahar
	Entry No :- 2016csb1043
	Date :- 26/11/18

	Purpose :-	

		1. Create Datagram Server and Client Handling Threads
		2. For Concurrent Requests apply Threading for new Client
*/

/*Library for utilising DataGram Sockets*/
import java.net.DatagramPacket; 
import java.net.DatagramSocket; 
import java.net.InetAddress; 
import java.io.*;
import java.lang.Integer;
import java.lang.Math;
import java.util.Arrays;

/*To Serilialize and DeSerialize Object*/
import org.apache.commons.lang3.SerializationUtils;

/*Implemented Threading for Handling of large requests*/
class RequestHandler extends Thread{

	private DatagramPacket pack;
	private DatagramSocket sock;

	RequestHandler(DatagramPacket pack, DatagramSocket socket){

		this.pack = pack;
		this.sock = socket;
	}

	public void run(){

		try{
			/*Deserialize the input recieved from Client*/
			byte[] response = pack.getData();

			//
			DataPacket res = SerializationUtils.deserialize(response);
			System.out.print("Recieved from IP "+pack.getAddress()+": ");
			res.print();
			/*Select Randomly between OK and ERROR*/
			
			String sendVal = (Math.random() <= 0.5 ? "OK" : "ERROR");
			byte[] sendData = SerializationUtils.serialize(new DataPacket(res.n, sendVal));
			//System.out.println(Arrays.toString(sendData)+ " ->"+sendData.length);
			//byte[] buff = {12, 15};
			DatagramPacket sendPack = new DatagramPacket(sendData,sendData.length, pack.getAddress(), pack.getPort());
			sock.send(sendPack);
			

		}catch(Exception e){

			System.out.println(e.getMessage());

		}
	}

}

public class Server{


	public static void main(String [] args) throws Exception{

		/*By Default Values of Ip,port and frequecy*/
		String ip = "localhost";
		int port = 8080;

		/*Handling CLI arguments*/
		for(int i = 0;i < args.length; i+= 2){

			/*Get Value corresponding to Specifier*/
			if(args[i].equals("-ip"))
				ip = args[i+1];
			else if(args[i].equals("-port"))
				port = Integer.parseInt(args[i+1]);
			else
				continue;
			
		}

		//System.out.println("IP : "+ip+" Port : "+port+" Freq : "+f); 

		InetAddress inet = InetAddress.getByName(ip);
		DatagramSocket socket = new DatagramSocket(port, inet);

		/*As UDP is stateless it closes itself after request So spawn new Thread at each request*/
		System.out.println("You can press Ctrl-C anytime you want to exit. Press :R (Colon R) to print datagram stats.");
		while(true){

			byte[] data = new byte[160];

			DatagramPacket pack = new DatagramPacket(data, 160);

			System.out.println("Waiting For next Datagram ........");
			socket.receive(pack);
		
			(new RequestHandler(pack, socket)).run();	
		}
	}


}
