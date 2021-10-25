import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Arrays;
import java.util.Scanner;


/* Да се състави клас книга Book, имплементиращ Comparable
== Частни полета: заглавие, име на автор, година на издаване, страници;
== 1.1 Подразбиращ се конструктор;
== 1.2 Експлицитен конструктор – по всички променливи;
== 1.3 Методи за четене/запис на член-променливите;
== 1.4 Метод за стрингова интерпретация;
== 1.5 Метод за еквивалентност;
== 1.6 Имплементация на интерфейса.*/
class Book implements Comparable {
    protected String book_title;
    protected String author;
    protected int pub_year;
    protected int page_num;

    public Book() {
        this.book_title = " "; this.author = " "; this.pub_year = 0; this.page_num = 0;
    }
    public Book(String book_title, String author, int pub_year, int page_num) {
        this.book_title = book_title;
        this.author = author;
        this.pub_year = pub_year;
        this.page_num = page_num;
    }

    public String getBook_title() { return book_title; }
    public void setBook_title(String book_title) { this.book_title = book_title; }
    public String getAuthor() { return author; }
    public void setAuthor(String author) { this.author = author; }
    public int getPub_year() { return pub_year; }
    public void setPub_year(int pub_year) { this.pub_year = pub_year; }
    public int getPage_num() { return page_num; }
    public void setPage_num(int page_num) { this.page_num = page_num; }

    @Override
    public String toString() {
        return "\nBook name: '" + book_title + '\'' +
                ", Author: " + author + '\'' +
                ", Publication Year: " + pub_year +
                ", Total page number: " + page_num ;
    }

    public boolean equals(Object obj) {
/*                    if (this == obj) return true;
        if (obj == null) return false;
        if (getClass() != obj.getClass())    // Проверка дали и двата са в еднакъв клас
            return false;

        Book other = (Book)obj;              // type-casting за да можем да сравняваме по лесно

        // Вариант 1:
        if (author == null) {
            if (other.author != null)
                return false;
        } else if (!author.equals(other.author))
                    return false;
        if (book_title == null) {
            if (other.book_title != null)
                return false;
        } else if (!book_title.equals(other.book_title))
            return false;
        if (pub_year != other.pub_year)
            return false;
        return true;*/
        // Вариант 2:                           // Ако сме сигурни че няма да има null или от друг клас
        Book other = (Book)obj;
        return page_num == other.page_num
                && pub_year == other.pub_year
                && book_title.equals(other.book_title)    // string
                && author.equals(other.author);           // string
    }

    // Имплементация на интерфейса
    @Override
    public int compareTo(Object o) {           // САМО ЗА INT!
        if (this.pub_year <((Book)o).pub_year)
            return -1;
        if (this.pub_year > ((Book)o).pub_year)
            return 1;
        return 0;

        //  return this.pub_year - ((Book)obj).pub_year;
    }
}


/*2. Да се състави клас Library
== Частен масив от книги;
== 2.1 Експлицитен конструктор с име на файл - public Library(String filename)
== Формат на файла:
== <заглавие>SP<име на автор>SP<година на издаване>SP<страници>CR
== 2.2 Метод за извеждане на масива на конзола;
== 2.3 Метод за сортиране на масива по година на издаване;
== 2.4 Метод, който изчислява и връща общия брой страници на книгите от масива;
== 2.5 Метод, който изчислява и връща броя книги, чиито страници са повече от зададен параметър;
== 2.6 Метод, който изчислява и върща колко книги от даден автор има в масива;
== 2.7 Метод, който изчислява и връща средната стойност на страниците на книгите от масива;
== 2.8 Метод, който изчислява и връща броя книги, които са издадени след определена година;
=? 2.9 Метод, който намира и връща заглавието на книгата, издадена най-късно.*/

class Library {
    private Book[] books = new Book[] {                           // Частен масив от книги;
            new Book("","",0,0),
            new Book("","",0,0),
            new Book("","",0,0),
            new Book("","",0,0),
            new Book("","",0,0),
            new Book("","",0,0),
            new Book("","",0,0)
    };

    public Library(String filename) {
        try {
            // bookname1 author2 2021 110
            Scanner in = new Scanner(new File(filename));
            int index = 0;

            while (in.hasNext()) {
                books[index++] = new Book(
                        in.next(),
                        in.next(),
                        in.nextInt(),
                        in.nextInt()
                );
            }
            in.close();

        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
    }

    public void print() {
        System.out.println(Arrays.toString(books));
    }
    public void sortArr() {
        Arrays.sort(books);    // is this why we did "compareTo" with pub_year?
    }

    public int totalPages() {
        int result = 0;
        for (Book cur : books) {
            result += cur.page_num;
        }
        return result;
    }

    public int morePages(int givenNum) {
        int result = 0;
        for (Book cur : books) {
            if (cur.page_num > givenNum) {
                result++;
            }
        }
        return result;
    }

    public int authorsBooks(String author_name) {
        int result = 0;
        for (Book cur : books) {
            if (cur.author.equals(author_name)) {
                result++;
            }
        }
        return result;
    }

    public double averagePages() {
        double result = totalPages();
        return result / books.length;
    }

    public int publishedAfter(int year) {
        int result = 0;
        for (Book cur : books) {
            if (cur.pub_year > year) {
                result++;
            }
        }
        return result;
    }

    // 2.9 Метод, който намира и връща заглавието на книгата, издадена най-късно
    public String findBookName() {
        sortArr();                                  // sort by year
        return books[books.length - 1].book_title;
    }
}

/*3. Да се състави MainClass с главна функция, която:
== 3.1 Създава обект от т.2, извежда;
== 3.2 Сортира масива, извежда;
== 3.3 Намира общият брой страници, извежда;
== 3.4 Намира брой книги със страници над зададена стойност, извежда;
== 3.5 Намира брой книги от даден автор, извежда;
== 3.6 Намира средната стойност на страниците, извежда;
== 3.7 Намира брой книги, издадени след определена година, извежда;
3.8 Намира заглавието на книгата, издадена последна, извежда.
*/
public class Main {
    public static void main(String[] args) {
        Library books = new Library("src/books.txt");
        books.print();

        System.out.println("\nBooks [SORTED]: ");
        books.sortArr();
        books.print();

        System.out.println("\nTotal Pages: " + books.totalPages());
        System.out.println("Books that have more pages than 105: " + books.morePages(105));
        System.out.println("Author1's books: " + books.authorsBooks("author1"));
        System.out.println("Average pages: " + books.averagePages());
        System.out.println("Books published after 2015" + books.publishedAfter(2015));
        System.out.println("Last published books title: " + books.findBookName());
    }
}
