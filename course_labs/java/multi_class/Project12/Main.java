/*
    Multi Threading CO4
    Implement a Reservation system which allows the persons to book seats. Define reserve
    method initially with 100 seats. Now create one or more person threads to book seats. At
    any time it should allow only one person thread to access the reserve method.
 */


class ReservationSystem {
    private int availableSeats = 100;

    public synchronized void reserve(String personName, int requestedSeats) {
        System.out.println(personName + " entered.");
        System.out.println("Available seats: " + availableSeats + " Requested seats: " + requestedSeats);

        if (availableSeats >= requestedSeats) {
            System.out.println("Seat Available. Reserve now :-)");
            availableSeats -= requestedSeats;
            System.out.println(requestedSeats + " seats reserved.");
        } else {
            System.out.println("Requested seats not available :-(");
        }

        System.out.println(personName + " leaving.");
        System.out.println("----------------------------------------------");
    }
}

class PersonThread extends Thread {
    private ReservationSystem reservationSystem;
    private String personName;
    private int requestedSeats;

    public PersonThread(ReservationSystem reservationSystem, String personName, int requestedSeats) {
        this.reservationSystem = reservationSystem;
        this.personName = personName;
        this.requestedSeats = requestedSeats;
    }

    @Override
    public void run() {
        reservationSystem.reserve(personName, requestedSeats);
    }
}

public class Main {
    public static void main(String[] args) {
        ReservationSystem reservationSystem = new ReservationSystem();

        // Create multiple person threads
        PersonThread person1 = new PersonThread(reservationSystem, "Person-1", 5);
        PersonThread person2 = new PersonThread(reservationSystem, "Person-2", 2);
        PersonThread person3 = new PersonThread(reservationSystem, "Person-3", 4);

        // Start the threads
        person1.start();
        person2.start();
        person3.start();
    }
}
