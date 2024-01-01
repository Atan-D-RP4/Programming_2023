import java.util.LinkedList;

class SharedBuffer {
    LinkedList<Integer> buffer = new LinkedList<>();
    int capacity = 2;

    public void produce() throws InterruptedException {
        int item = 1;
        while (true) {
            synchronized (this) {
                while (buffer.size() == capacity)
                    wait();

                System.out.println("Producer produced: " + item);
                buffer.add(item++);
                notify();
                Thread.sleep(1000);
            }
        }
    }

    public void consume() throws InterruptedException {
        while (true) {
            synchronized (this) {
                while (buffer.isEmpty())
                    wait();

                int consumedItem = buffer.removeFirst();
                System.out.println("Consumer consumed: " + consumedItem);
                notify();
                Thread.sleep(1000);
            }
        }
    }
}

public class ProducerConsumerExample {
    public static void main(String[] args) {
        SharedBuffer sharedBuffer = new SharedBuffer();

        Thread producerThread = new Thread(() -> {
            try {
                sharedBuffer.produce();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        });

        Thread consumerThread = new Thread(() -> {
            try {
                sharedBuffer.consume();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        });

        producerThread.start();
        consumerThread.start();
    }
}
