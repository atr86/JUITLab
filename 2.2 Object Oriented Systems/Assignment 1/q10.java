import java.util.Scanner;

class Soldbook{
    String author;
    String title;
    String publisher ;
    float  cost;
    int  stock;
    public Soldbook(String title, String author, String publisher, float cost, int stock) {
        this.title = title;
        this.author = author;
        this.publisher = publisher;
        this.cost = cost;
        this.stock = stock;
    }
    public Soldbook(String title,String author){
        this.title=title;
        this.author=author;
    }
    public String getAuthor() {
        return author;
    }

    public String getTitle() {
        return title;
    }

    public String getPublisher() {
        return publisher;
    }

    public float getCost() {
        return cost;
    }

    void Sellcopy(int copy){
        if(stock>=copy){
            float total_cost= cost* copy;
            System.out.println("Total cost :: "+total_cost);
            System.out.println("Thanks for buying from us. ");
            stock-=copy;
        }
        else{
            System.out.println("Sorry !! we are out of stock.");
        }
    }
}

class book_db{

    Soldbook inventory[];

    book_db(){
        initialize_inventory();
    }

    void initialize_inventory(){
    inventory= new Soldbook[5] ;
    inventory[0] = new Soldbook("Life of Pi", "Yann Martel", "PublisherA", 10.99f, 3);
    inventory[1] = new Soldbook("The Jungle Book", "Rudyard Kipling", "PublisherB", 12.99f, 2);
    inventory[2] = new Soldbook("Harry Potter : vol 1", "J. K. Rowling", "PublisherC", 15.99f, 1);
    inventory[3] = new Soldbook("Pride and Prejudice", "Jane Austen", "PublisherD", 9.99f, 3);
    inventory[4] = new Soldbook("Frankenstein", "Mary Shelley", "PublisherE", 8.99f, 1);
    }
    void search_book(Soldbook ob, int copy){
        boolean found = false;
        for(int i=0;i<5;i++){
            if(inventory[i].title.equalsIgnoreCase(ob.title) && inventory[i].author.equalsIgnoreCase(ob.author)){
                System.out.println("This book is available in our stock.");
                inventory[i].Sellcopy(copy);
                found=true;
                break;
            }
        }

            if(!found){
                System.out.println("Sorry!! this book is not in our stock .");
        }
    }
    
    public static void main(String[] args) {
        book_db ob= new book_db();
        Scanner ob1 =new Scanner(System.in);
        System.out.println("Enter the Title name: ");
        String title= ob1.nextLine().trim();
        System.out.println("Enter the author : ");
        String author= ob1.nextLine().trim();
        Soldbook b1 = new Soldbook(title,author);
        System.out.println("Enter the number of copies you want: ");
        int copy= ob1.nextInt();
        ob.search_book(b1,copy);

    }
}