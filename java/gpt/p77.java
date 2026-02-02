class Person {
    int status;
}

public class Main {
    public static Person createPerson() {
        Person p = new Person();  // allocates memory for object
        p.status = 0;
        return p;
    }

    public static void main(String[] args) {
        Person newPerson = createPerson();
        System.out.println("Person status: " + newPerson.status);
    }
}
