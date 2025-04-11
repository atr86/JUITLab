// Create a base class “Automobile”. An Automobile contains data members ‘make’, ‘type’,
// ‘maxSpeed’, ‘price’, ‘mileage’, ‘registrationNumber’ etc. with their reader/writer methods. Now
// create two sub-classes “Track” and “Car”. Track has data members ‘capacity’, ‘hoodType’,
// ‘noOfWheels’ etc. Car has data members ‘noOfDoors’, ‘seatingCapacity’ and their reader/writer
// methods. Create a main() function to demonstrate this.

class Automobile
{
    private String make;
    private String type;
    private int maxSpeed;
    private int price;
    private int mileage;
    private int regno;
    public String getMake() {
        return make;
    }
    public void setMake(String make) {
        this.make = make;
    }
    public String getType() {
        return type;
    }
    public void setType(String type) {
        this.type = type;
    }
    public int getMaxSpeed() {
        return maxSpeed;
    }
    public void setMaxSpeed(int maxSpeed) {
        this.maxSpeed = maxSpeed;
    }
    public int getPrice() {
        return price;
    }
    public void setPrice(int price) {
        this.price = price;
    }
    public int getMileage() {
        return mileage;
    }
    public void setMileage(int mileage) {
        this.mileage = mileage;
    }
    public int getRegno() {
        return regno;
    }
    public void setRegno(int regno) {
        this.regno = regno;
    }
    public void display() {
        System.out.println("Make: " + make);
        System.out.println("Type: " + type);
        System.out.println("Max Speed: " + maxSpeed);
        System.out.println("Price: " + price);
        System.out.println("Mileage: " + mileage);
        System.out.println("Registration Number: " + regno);
    }
}
class Track extends Automobile
{
    private int cap;
    private String htype;
    private int now;
    public int getCap() {
        return cap;
    }
    public void setCap(int cap) {
        this.cap = cap;
    }
    public String getHtype() {
        return htype;
    }
    public void setHtype(String htype) {
        this.htype = htype;
    }
    public int getNow() {
        return now;
    }
    public void setNow(int now) {
        this.now = now;
    }
    public void display() {
        super.display();
        System.out.println("Capacity: " + cap+" kg");
        System.out.println("Hood Type: " + htype);
        System.out.println("Number of Wheels: " + now);
    }
}

class Car extends Automobile
{
    private int nod;
    private int seatCap;
    public int getNod() {
        return nod;
    }
    public void setNod(int nod) {
        this.nod = nod;
    }
    public int getSeatCap() {
        return seatCap;
    }
    public void setSeatCap(int seatCap) {
        this.seatCap = seatCap;
    }
    public void display() {
        super.display();
        System.out.println("Number of Doors: " + nod);
        System.out.println("Seating Capacity: " + seatCap);
    }
}


public class q13
{
    public static void main(String args[])
    {
        Car c= new Car();
        Track t= new Track();
        c.setMake("Toyota");
        c.setMaxSpeed(100);
        c.setMileage(85);
        c.setPrice(1900000);
        c.setRegno(123445364);
        c.setNod(4);
        c.setType("Luxury Car");
        c.setSeatCap(8);
        t.setMake("Toyota");
        t.setMaxSpeed(100);
        t.setMileage(85);
        t.setPrice(1900000);
        t.setRegno(123445364);
        t.setType("Luxury Car");
        t.setHtype("removable");
        t.setNow(4);
        t.setCap(90);
        System.out.println("Car");
        c.display();
        System.out.println("Track");
        t.display();
    }
}