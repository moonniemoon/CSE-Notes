import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.util.Arrays;
import java.util.Scanner;
/*
Задача за упражнение 5 (I група доц. Вл. Николов )  – Тема създаване на интерфейси за файлов вход/изход
I. Да се състави интерфейс IFile с методи:
void save()
void load()
Примерно съдържание на входния файл:
1 1 2 3 255
1 2 3 3 255
1 3 4 5 255
1 4 5 6 255
1 5 2 3 255
1 6 3 3 255
1 7 4 5 255
1 8 5 6 255
1 9 2 3 255
1 10 3 3 255

*/
interface IFile{
void save();
void load();
}



/*      II. Да се създаде клас RectangleArrayInterface като се промени клас RectangleArray(),
съдържащ частен масив от обекти ColorRectangle, който да имплементира интерфейса IFile
Промени:
II.1. Да се добавят 2 частни полета с тип низ за съхраняване на имена на файлове – входен и изходен.
Конструктори и методи:
II.2. Експлицитен конструктор с 2 имена на файлове-за вход и изход.
Формат на файловете:
10 правоъгълника.
Формат:<x1>SP<y1>SP<x2>SP<y2><SP><color>CR
Публични методи (допълнение към съществуващите):
II.3. Имплементация на интерфейсните методи
II.4. Изтриване на данните;
II.5. Промяна на данните в масива по указан индекс;
За домашно : II.6. Метод за изчисляване на броя правоъгълниците, които се припокриват от някой друг правоъгълник (еднократно)
За домашно : II.7. Метод за изчисляване на обграждащ правоъгълник
За домашно : II.8. Метод за изчисляване на общ (сечение) правоъгълник*/
public class RectangleArrayInterface implements IFile {
        private ColorRectangle[] aColl = new ColorRectangle[10];
        private String inputFile = "defaultIn.txt";
        private String outputFile = "defaultOut.txt";
        
        public RectangleArrayInterface(String fileNameIn, String fileNameOut ) {
            inputFile = fileNameIn;
            outputFile = fileNameOut;
            load();
        //	try {
        //   // 1 1 2 3 255
        //		RandomAccessFile myFile = new RandomAccessFile(fileName,"r");
        //		String strLine;
        //		String[] res;
        //		int ind=0;
        //		while( (strLine=myFile.readLine()) != null){
        //			res=strLine.split(" ");
        ////			Integer oIntX1 = Integer.valueOf(res[0]);	// "1" => 1
        ////			Long oColor = Long.valueOf(res[4]);
        //			ColorRectangle oRectangle = new ColorRectangle(
        //					Integer.valueOf(res[0]).intValue(),
        //					Integer.valueOf(res[1]).intValue(),
        //					Integer.valueOf(res[2]).intValue(),
        //					Integer.valueOf(res[3]).intValue(),
        //					Long.valueOf(res[4]).longValue()
        //					);
        //			aColl[ind++] = oRectangle;
        //		}
        //		myFile.close();
        //	}catch (FileNotFoundException e) {
        //		e.printStackTrace();
        //	}catch (IOException e) {
        //		e.printStackTrace();
        //	}
        }
        public void printColl() {
            System.out.println(Arrays.toString(aColl));
        }
        
        //II.3. Имплементация на интерфейсните методи
        @Override
        public void save() {
            try {
                RandomAccessFile fout = new RandomAccessFile(outputFile,"rw");
                for (ColorRectangle current : aColl) {
                    //Формат:<x1>SP<y1>SP<x2>SP<y2><SP><color>CR
                    fout.writeBytes(current.getix1() + " ");
                    fout.writeBytes(current.getiy1() + " ");
                    fout.writeBytes(current.getix2() + " ");
                    fout.writeBytes(current.getiy2() + " ");
                    fout.writeBytes(current.getColor() + "\r\n");
                }
                fout.close();
            } catch (FileNotFoundException e) {
                e.printStackTrace();
            } catch (IOException e) {
                e.printStackTrace();
            }
        
        }
        @Override
        public void load() {
            try {
                Scanner iStream = new Scanner(new File(inputFile));
                int index = 0;
                while(iStream.hasNext()) {
                    //Формат:<x1>SP<y1>SP<x2>SP<y2><SP><color>CR
        //				int x1=iStream.nextInt();
        //				long clr = iStream.nextLong();
                    aColl[index++]=new ColorRectangle(
                            iStream.nextInt(),
                            iStream.nextInt(),
                            iStream.nextInt(),
                            iStream.nextInt(),
                            iStream.nextLong());
                }
                iStream.close();
            } catch (FileNotFoundException e) {
                e.printStackTrace();
            }
        
        }
        
        // II.4. Изтриване на данните;
        public void clearColl() {
            aColl = null;
        }
        
        // II.5. Промяна на данните в масива по указан индекс;
        public void changeRectangle(int index, ColorRectangle oRectangle) {
            aColl[index]=oRectangle;
        }
        
        //	III.3.Изчисляване на сумарна площ използва -double calcSumArea()
        public double calcSumArea() {
            double result = 0.0;
            for(ColorRectangle current : aColl) {
                result += current.calcArea();
            }
            return result;
        }
        
        // III.4. Изчисляване на сумарен периметър използва double calcSumPerimeter()
        public double calcSumPerimeter() {
            double result = 0.0;
            for(ColorRectangle current : aColl) {
                result += current.calcPerimeter();
            }
            return result;
        }
}
