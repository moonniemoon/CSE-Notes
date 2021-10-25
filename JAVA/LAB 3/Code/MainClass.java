import javax.lang.model.type.ArrayType;
import java.io.*;
import java.util.*;

/* Да се състави клас съхраняващ множество от правоъгълници: RectangleCollection:
за съхраняване на ColorRectangle:
Член (частен) интерфейс SortedSet, тип TreeSet за съхраняване на множество правоълъници
* Конструктори/Методи:
* 1.1) Подразбиращ се
* 1.2) Експицитен по име на файл: RectangleCollection(String )
* Файлът съдържа правоълъници. Формат: x1 y1 x2 y2 color
* Example:
-10 -10 6 10 255
-1 -1 10 6 255
-2 -2 10 6 255
-3 -1 10 6 255
-1 -1 10 6 255
*  1.3) Добавя подадения параметър към колекцията void addRectangle(...)
*  1.4) Изчислява заграждащ правоъгълник: ColorRectangle calcUnionColl()
*  1.5) Изчислява минимален по площ правоъгълник: ColorRectangle calcMin()
*  1.6) Изчислява максимален по площ правоъгълник: ColorRectangle calcMax()
*  1.7) Изчислява/връща броя на припокритите от някой друг правоъгълник правоъгълници int calcNested()
*  1.8) Връща броя елементи в множеството int calcSize()
*  1.9) Извежда колекцията void printColl()
*  1.10) Изчислява/връща суматна площ double calcSumArea()
*  1.11) Изчислява/връща сумарен периметър  double calcSumPerimeter()
*  1.12) Изчислява/връща списък с обратен ред List reverseList()
*  1.13) Търси правоъгълника параметър  boolean findRect(ColorRectangle toFind)
 */
class MainClass implements IFile { // RECTANGLE COLLECTION
    private Set<ColorRectangle> oColl;

    private String inputFile = "defaultIn.txt";
    private String outputFile = "defaultOut.txt";

    public MainClass() {
        oColl = new TreeSet<ColorRectangle>();
    }
    public MainClass (String inputFile, String outputFile) {
        oColl = new TreeSet<ColorRectangle>();
        this.inputFile = inputFile;
        this.outputFile = outputFile;
        load();
    }

    @Override
    public void load() {
        try {
            // 1 1 1 1 255
            oColl = new TreeSet<ColorRectangle>();
            Scanner in = new Scanner(new File(inputFile));
            int index = 0;

            while (in.hasNext()) {
                ColorRectangle colorRectangle = new ColorRectangle(
                        in.nextInt(),
                        in.nextInt(),
                        in.nextInt(),
                        in.nextInt(),
                        in.nextLong()
                );
                oColl.add(colorRectangle);
            }
            in.close();

        } catch (FileNotFoundException e) {
            System.out.println("File not found!");
        }
    }

    @Override
    public void save() {
        try {
            RandomAccessFile fout = new RandomAccessFile(outputFile, "rw");  // read-write

            if (oColl.size() > 0) {
                fout.setLength(0);
            }

            for (ColorRectangle cur : oColl) {
                fout.writeBytes(cur.getix1() + " ");
                fout.writeBytes(cur.getiy1() + " ");
                fout.writeBytes(cur.getix2() + " ");
                fout.writeBytes(cur.getiy2() + " ");
                fout.writeBytes((int)cur.getColor() + "\r\n");
            }
            fout.close();

        } catch (EOFException e) {
            System.out.println("End Of File!");
        } catch (FileNotFoundException e) {
            System.out.println("FileNotFound");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public boolean remove() {
        try {

            RandomAccessFile fout = new RandomAccessFile(outputFile,"rw");
            if(oColl.size()>0){
                fout.setLength(0);
            }
            fout.close();


        } catch(EOFException e){
            System.out.println("End Of File!");
            return false;
        }
        catch(FileNotFoundException e){
            System.out.println("FileNotFound");
            return false;
        }
        catch(IOException e){
            System.out.println("IOException!");
            return false;
        }
        return true;
    }

    public void printColl(Collection c) {
        for(Iterator It = c.iterator(); It.hasNext();){
            System.out.println(It.next().toString());
        }
    }

    // 1.3) Добавя подадения параметър към колекцията void addRectangle(...)
    public void addRectangle(ColorRectangle rect) {
        oColl.add(rect);
    }

    // 1.4) Изчислява заграждащ правоъгълник: ColorRectangle calcUnionColl()
    public ColorRectangle calcUnionColl() {
        ColorRectangle result = new ColorRectangle(0,0,0,0,0);
        for (Iterator it = oColl.iterator(); it.hasNext();) {
            ColorRectangle cur = (ColorRectangle)it.next();
            result = result.unionRect(cur);
        }
        return result;
    }

    // 1.5) Изчислява минимален по площ правоъгълник: ColorRectangle calcMin()
    public ColorRectangle calcMin() {
        ColorRectangle result = new ColorRectangle(1000, 1000, 1000, 1000, 1000);
        Iterator it = oColl.iterator();
        if (it.hasNext()) {
            result = (ColorRectangle)((SortedSet)oColl).last();
        }
        return result;
    }

    // 1.6) Изчислява максимален по площ правоъгълник: ColorRectangle calcMax()
    public ColorRectangle calcMax() {
        ColorRectangle result = new ColorRectangle(-1000, -1000, -1000, -1000, -1000);
        Iterator it = oColl.iterator();
        if (it.hasNext()) {
            result = (ColorRectangle) it.next();
        }
        return result;
    }

    // 1.13) Търси правоъгълника параметър  boolean findRect(ColorRectangle toFind)
    public boolean findRect(ColorRectangle toFind) {
        return oColl.contains(toFind);
    }

    // 1.12) Изчислява/връща списък с обратен ред List reverseList()
    public List reverseList() {
        List<ColorRectangle> list = new ArrayList<ColorRectangle>(oColl);
        List<ColorRectangle> listResult = new ArrayList<ColorRectangle>();
        for (ListIterator it = list.listIterator(list.size()); it.hasPrevious(); ) {  // reverse iterator ?
            ColorRectangle prev = (ColorRectangle) it.previous();
            listResult.add(prev);
        }
        return listResult;
    }

    // 1.10) Изчислява/връща суматна площ double calcSumArea()
    public double calcSumArea() {
        double result = 0;

        for (Iterator it = oColl.iterator(); it.hasNext(); ) {
            result += ((ColorRectangle)it.next()).calcArea();
        }

        return result;
    }

    // 1.11) Изчислява/връща сумарен периметър  double calcSumPerimeter()
    public double calcSumPerimeter() {
        double result = 0;
        for (Iterator it = oColl.iterator(); it.hasNext();) {
            result += ((ColorRectangle)it.next()).calcPerimeter();
        }
        return result;
    }

    // 1.8) Връща броя елементи в множеството int calcSize()
    public int calcSetSize() {
        return oColl.size();
    }

    private int counter (ColorRectangle obj) {
        int result = 0;

        Iterator it = oColl.iterator();
        ColorRectangle cur = new ColorRectangle();

        while (it.hasNext()) {
            cur = (ColorRectangle) it.next();
            if ((obj != cur)
                    && (obj.getix1() >= cur.getix1())
                    && (obj.getiy1() <= cur.getiy1())
                    && (obj.getix2() >= cur.getix2())
                    && (obj.getiy2() <= cur.getiy2())) {
                result++;
                break;
            }
        }
        return result;
    }

    public int countNesting() {
        int allNested = 0;
        for (ColorRectangle cur : oColl) {
            allNested += counter(cur);
        }
        return allNested;
    }

    public void deleteCollection() {
        oColl.clear();
    }





/*Главна функция
* Създава обект RectangleCollection по зададен входен файл rects.txt, добавя елемент 2, 2, 400, 400, 255, извежда
* Изчислява обграждащ правоъгълник
* Изчислява мин. правоъгълник
* Изчислява макс. правоъгълник
* Изчислява броя на припрокритите правоъгълници
* Изчислява списък в обратен ред
* Изчислява сума от площи
* Изчислява сума от периметри
* Изчислява размерност
* */

    public static void main(String[] args) {
        try{
            MainClass obj = new MainClass("src/rectsIn.txt","src/rectsOut.txt");
            obj.addRectangle(new ColorRectangle(2, 2, 400, 400, 255));
            obj.printColl(obj.oColl);
            System.out.println("Union Result:"+obj.calcUnionColl());
            System.out.println("Min Result:"+obj.calcMin());
            System.out.println("Max Result:"+obj.calcMax());
            System.out.println("Reverse:"+obj.reverseList());
            System.out.println("Sum Area:"+obj.calcSumArea());
            System.out.println("Sum Perimeter:"+obj.calcSumPerimeter());
            System.out.println("Size:"+obj.calcSetSize());
            System.out.println("Nesting:"+obj.countNesting());
            obj.save();
            obj.deleteCollection();
            obj.load();
            System.out.println("Reload:");
            obj.printColl(obj.oColl);
            obj.remove();
        }catch(Exception ex){
            System.out.println(ex.getMessage());
        }
    }
}
