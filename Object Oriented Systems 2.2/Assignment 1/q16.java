// Write two interfaces “Fruit” and “Vegetable” containing methods ‘hasAPeel’ and ‘hasARoot’.
// Now write a class “Tomato” implementing Fruit and Vegetable. Instantiate an object of Tomato.
// Print the details of this object.

interface Fruit{
    boolean hasAPeel();
    boolean hasARoot();
}
interface Vegetable{
    boolean hasAPeel();
    boolean hasARoot();
}

class Tomato implements Fruit, Vegetable
{
    public boolean hasAPeel()
    {
        return true;
    }
    public boolean hasARoot()
    {
        return false;
    }
}

public class q16{
    public static void main(String args[])
    {
        Tomato ob= new Tomato();
        System.out.println("Tomato has a Peel "+ob.hasAPeel());
        System.out.println("Tomato has a Root "+ob.hasARoot());
    }
}