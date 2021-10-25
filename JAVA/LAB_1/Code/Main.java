        import javax.lang.model.type.ArrayType;
        import java.util.Arrays;
        import java.util.GregorianCalendar;

        interface ILibraryBook {
            void get(Reader rdr);
            void ret();
        }

        interface IReader {
            void get(LibraryBook LB);
            void ret(LibraryBook LB);
        }

        /*1. Скрити (Защитени) членове име, дата на постъпване в университет, успех:
        име : String
        дата на раждане : GregorianCalendar
        успех : double
        Конструктор:
        public Applicant(GregorianCalendar birth, String name, double uspeh)
        Методи : get/set toString*/
        class Applicant {
            protected String name;
            protected GregorianCalendar date_ob;
            protected double GPA;

            public Applicant(GregorianCalendar date_ob, String name, double GPA) {
                this.name = name;
                this.date_ob = date_ob;
                this.GPA = GPA;
            }

            public String getName() { return name; }
            public GregorianCalendar getDate_ob() { return date_ob; }
            public double getGPA() { return GPA; }
            public void setName(String name) { this.name = name; }
            public void setDate_ob(GregorianCalendar date_ob) { this.date_ob = date_ob; }
            public void setGPA(double GPA) { this.GPA = GPA; }

            @Override
            public String toString() {
                return "\n\t\tName = '" + name + '\'' +
                        "\n\t\tGPA = " + GPA + "\n";
            }
        }

        /*Да се състави клас пакетен достъп Student, наследник на Applicant имплементиращ Comparable
        скрити членове:
        фак. номер : String
        Конструктори:
        public Student(String name, String f_nom)
        public Student(GregorianCalendar date, String name, double uspeh, String f_nom)
        Методи : get/set toString equals*/
        class Student extends Applicant implements Comparable {
            protected String str_fNum;

            public Student(String name, String str_fNum) {
                super(new GregorianCalendar(), name, 0.0);    // new GregorianCalendar() значи че създава календарен обект по подразбиране
                this.str_fNum = str_fNum;
            }
            public Student(GregorianCalendar date_ob, String name, double GPA, String str_fNum) {
                super(date_ob, name, GPA);
                this.str_fNum = str_fNum;
            }

            public String getStr_fNum() { return str_fNum; }
            public void setStr_fNum(String str_fNum) { this.str_fNum = str_fNum; }

            @Override
            public String toString() {
                return "Student:  " +
                        "Faculty Number = '" + str_fNum + '\'' +
                        ", " + super.toString() + "\n" ;
            }

            public boolean equals(Student o) {
                return (str_fNum.compareTo(((Student)o).str_fNum) == 0);
            }

            @Override
            public int compareTo(Object o) {
                return str_fNum.compareTo((((Student)o).str_fNum));
            }
        }

        /*Да се състави клас пакетен достъп Reader, наследник на Student, имплементиращ интерфейс
        IReader,Comparable:
        Частно поле LibraryBook readerBook
        1. Експлицитни конструктори:
        public Reader(String nm,String fn)
        public Reader(GregorianCalendar date, String name, double uspeh, String f_nom)
        2.Методи четене/запис еквивалентност и стрингова интерпретация:
        get/set,toString()
        */
        class Reader extends Student implements Comparable, IReader {

            private LibraryBook readerBook = new LibraryBook();

            public Reader(String name, String str_fNum) {
                super(new String(name), new String(str_fNum));
            }

            public Reader(GregorianCalendar date_ob, String name, double GPA, String str_fNum) {
                super(date_ob, new String(name), GPA, new String(str_fNum));
            }

            @Override
            public void get(LibraryBook LB) {
                readerBook = LB;
            }

            @Override
            public void ret(LibraryBook LB) {
                LB.ret();
                readerBook = new LibraryBook();
            }

            @Override
            public int compareTo(Object o) {
                return str_fNum.compareTo(((Reader)o).str_fNum);
            }

            public boolean equals(Object o) {
                if (this.str_fNum.compareTo(((Reader)o).str_fNum) != 0)
                    return true;
                else return false;
            }
        }

        /* Да се състави клас пакетен достъп LibraryBook, имплиментиращ ILibraryBook,Comparable:
        public class LibraryBook implements ILibraryBook,Comparable
        1.Частни членове:
        Читател : Reader
        Име на книга: String
        Статус:boolean
        2. Експлицитен конструктор
        public LibraryBook(String bn,boolean st)
        3. Методи четене/запис,за сравнение и стрингова интерпретация:
        */
        class LibraryBook implements ILibraryBook, Comparable {
            private Reader person;
            private String book_name;
            private boolean status;

            public LibraryBook() { }
            public LibraryBook(String book_name, boolean status) {
                this.person = new Reader("N/A", "N/A");
                this.book_name = new String(book_name);
                this.status = status;
            }

            public Reader getPerson() { return person; }
            public void setPerson(Reader person) { this.person = person; }
            public String getBook_name() { return book_name; }
            public void setBook_name(String book_name) { this.book_name = book_name; }
            public boolean isStatus() { return status; }
            public void setStatus(boolean status) { this.status = status; }

            @Override
            public void get(Reader rdr) {
                person.setName(rdr.name);
                person.setStr_fNum(rdr.str_fNum);
                status = true;
            }
            @Override
            public void ret() {
                person.name = "N/A";
                person.str_fNum = "N/A";
                status = false;
            }

            @Override
            public String toString() {
                return "\nBook_name = '" + book_name + '\'' +
                        ", Status = " + status;
            }
            @Override
            public int compareTo(Object o) {
                return book_name.compareTo(((LibraryBook)o).book_name);
            }
        }

        /*4.1. Създава масив от обекти от VI с данни за книги
        4.2. Симулира заемане1 от библиотека, Извежда;
        4.3. Симулира заемане2 от библиотека, Извежда;
        4.4. Сортира, извежда
        4.5. Проверява за еквивалентност, извежда*/
        public class Main {
            public static void main(String[] args) {
                Reader reader1 = new Reader("Celine", "19621962");
                LibraryBook[] books = new LibraryBook[] {                              // should i add "new LibraryBook[]"
                        new LibraryBook("The Great Gatsby", true),
                        new LibraryBook("Pinocchio", false),
                };

                /*LibraryBook[] books = new LibraryBook[2];
                books[0] = new LibraryBook("The Great Gatsby", false);
                books[0] = new LibraryBook("Pinocchio", false);
                */

                books[0].get((Reader) new Reader("Celine", "19621962"));
                System.out.println(reader1.toString());
                books[1].get((Reader) new Reader("Marcelin", "19621111"));

                System.out.println("ALL THE BOOKS: " + Arrays.toString(books));
                Arrays.sort(books);
                // System.out.println("All: " + Arrays.toString(books));

                books[0].ret();
                System.out.println(books[0]);

                if (books[0].compareTo(books[1]) == 0) {
                    System.out.println(books[0] + " is equal to " + books[1]);
                } else {
                    System.out.println(books[0] + " is NOT equal to " + books[1]);
                }
            }
        }
