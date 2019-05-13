/*

	Name :- Siddharth Nahar
	Entry No :- 2016csb1043
	Date :- 26/11/18

	Purpose :-	

		1. Create Datagram Client which Send Requests to Server 
		2. Send f requests per sec to server handled by Timer Object
*/

/*Library for utilising DataGram Sockets*/
import java.net.DatagramPacket; 
import java.net.DatagramSocket; 
import java.net.InetAddress; 
import java.io.*;
import java.lang.Integer;

/*Timer and TimerTask for Sheduling request according to frequency*/
import java.util.Timer;
import java.util.TimerTask;
import java.util.Arrays;
import java.util.List;
import java.util.ArrayList;
/*To Serilialize and DeSerialize Object*/
import org.apache.commons.lang3.SerializationUtils;

/*Class to send data and recieve response */
class AcceptResponse extends TimerTask{

	DatagramSocket socket;
	int n;
	long timeStart, timeEnd;
	AcceptResponse(DatagramSocket socket, int n){
		
		this.socket = socket;
		this.n = n;
		this.timeStart = 0;
		this.timeEnd = 0;
	}

	public void run(){

		try{
			
			DataPacket objSend = new DataPacket(n, null);
	
			if(this.n == 1)
				this.timeStart = System.nanoTime();			

			if(this.n > 10){

				this.timeEnd = System.nanoTime();

				long timeElapsed = this.timeEnd - this.timeStart;
				
				double avgTime = timeElapsed*1.0/(1000000*10*2);
		
				System.out.println("Average time To Reach Server : "+avgTime+"ms");
				this.cancel();
				System.exit(0);
			}

			this.n++;
			byte[] buff = SerializationUtils.serialize(objSend);
			
			//System.out.println(Arrays.toString(buff)+ " "+buff.length);
			DatagramPacket sendData = new DatagramPacket(buff, buff.length);

			System.out.println("Started Sending .....");
			socket.send(sendData);

			
			byte[] dataRecv = new byte[160];

			DatagramPacket packRecv = new DatagramPacket(dataRecv, 160, socket.getInetAddress(), socket.getPort());
			socket.receive(packRecv);

			byte[] res = packRecv.getData();
			DataPacket objRecv = SerializationUtils.deserialize(res);
			System.out.println("Recieved From Server : n="+objRecv.n+","+objRecv.z);
			
			System.out.println("\n");

		}catch(Exception e){

			System.out.println(e.getMessage());
		}
	}

}

public class Client{

	public static void main(String[] args)throws Exception{

		/*By Default Values of Ip,port and frequecy*/
		String ip = "localhost";
		int port = 8080, f = 10;

		/*Handling CLI arguments*/
		for(int i = 0;i < args.length; i+= 2){

			/*Get Value corresponding to Specifier*/
			if(args[i].equals("-ip"))
				ip = args[i+1];
			else if(args[i].equals("-port"))
				port = Integer.parseInt(args[i+1]);
			else
				f = Integer.parseInt(args[i+1]);
			
		}

		/*Create Socket and Address and connect it to Server*/
		InetAddress inet = InetAddress.getByName(ip);
		DatagramSocket socket = new DatagramSocket();

		socket.connect(inet, port);

		int n = 1;
		AcceptResponse Obj = new AcceptResponse(socket, n);

		System.out.println("You can press Ctrl-C anytime you want to exit.");
		Timer timer = new Timer();

		
		timer.scheduleAtFixedRate(Obj, 0, 10);
		//timer.cancel();

		//timer.purge();
		
	}

}
