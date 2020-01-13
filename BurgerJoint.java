import java.util.ArrayList;

public class BurgerJoint {
	static ArrayList<Burger> buffer = new ArrayList<Burger>();
	static int bufferCounter = 0;
	static int bufferSize = 5;
	static int buf;
	static int p = 0;
	static int c = 0;
	static int n = 10;

	public static class Producer extends Thread{
		int a = 0;
		public void run(){
			System.out.println("Producer Starting");
			while(p < n){
				a = (int)Math.random() * 100;
				System.out.println("Making a Burger: " + p);
				while(a != 0){
					a = a - 1;
				}

				if (bufferCounter < bufferSize){
					p = p + 1;
					buffer.add( new Burger());
					bufferCounter = bufferCounter + 1 ;
					System.out.println("Burger in buffer: " + bufferCounter);
				}
				else {
					System.out.println("Buffer is full");
				}
			}
			System.out.println("Finished Making Burgers");
		}
	}
	public static class Consumer extends Thread{
		int b = 0;
		public void run(){
			System.out.println("Consumer Starting");
			while(c < n){


				b = (int)Math.random() * 100;
				while(b != 0){
					b = b - 1;
				}

				System.out.println("Eating Burger: " + c);
				
				if (bufferCounter > 0){
					c = c + 1;
					
					buffer.remove(0);
					bufferCounter = bufferCounter - 1 ;
					System.out.println("Burger in buffer: " + bufferCounter);
				}
				else {
					System.out.println("We need burger!");
				}
			}
			System.out.println("Finished Eating Burgers");
		}
	}
	
	public static class Burger{
		public Burger(){};
	}

	public static void main(String[] args) {		
		
		Producer producer = new Producer();
		Consumer consumer = new Consumer();

		producer.start();
		consumer.start();
	}
}
