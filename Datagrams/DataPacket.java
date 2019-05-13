/*

	Name :- Siddharth Nahar
	Entry No :- 2016csb1043
	Date :- 26/11/18

	Purpose :- 

		1. Serizable class to store payload of Client
		2. Creates random float,String
*/


/*Import Common text to generate Random String,Random number for Random Numbers*/
import org.apache.commons.text.RandomStringGenerator;
import java.util.Random;
import java.io.Serializable;


/*Implements Serializable for converting to byte array and reconstruct*/
public class DataPacket implements Serializable{

	/*Contents of Payload*/
	public int n;
	public float x, y;
	public String z;

	public DataPacket(int n, String z){

		/*Initialise DataSequence number*/
		this.n = n;
		Random rand = new Random();

		/*Initialize x, y with random floats*/
		this.x = rand.nextFloat()*100;
		this.y = rand.nextFloat()*100;

		if(z == null){
			/*Create Random String Generator Object for creation of Random String between 20,50 characters*/
			RandomStringGenerator generator = new RandomStringGenerator.Builder().withinRange('a', 'z').build();
			this.z = generator.generate(20, 50);
		}else{

			/*Assign Randomly OK or Error to Z*/
			this.z = z;
		}

	}

	public void print(){

		
		System.out.println("{n="+n+", x="+x+", y="+y+", z="+z+"}\n"); 
	}
}
