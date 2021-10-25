    import java.io.*;
    import java.util.*;

    interface ICalc {
        double perimeter();
        double area();
    }

    interface IFile {
        void save(); // запис
        void load(); // четене
        void change(Object first, Object Second); // проманя
    }

    abstract class GraphicalObj implements Comparable, ICalc {
        protected long red, blue, green, color;
        protected int topLeftX, topLeftY, height, width;
        final static int BYTE_MASK = 255;

        public void setRed(long red) { this.red = red; color2rgb(); }
        public void setGreen(long green) { this.green = green; color2rgb(); }
        public void setBlue(long blue) { this.blue = blue; color2rgb(); }

        private void rgb2colors() {
            red = color >>> 16;                    // 2 ^ 16
            green = (color >>> 8) & BYTE_MASK;     // 2 ^ 8
            blue = color & BYTE_MASK;
        }
        private void color2rgb() {
            color = (red << 16) | (green << 8) | (blue);  // Bitwise or |
        }

        public GraphicalObj() { }
        public GraphicalObj(long color, int topLeftX, int topLeftY, int height, int width) {
            this.color = color;
            rgb2colors();
            this.topLeftX = topLeftX;
            this.topLeftY = topLeftY;
            this.height = height;
            this.width = width;
        }

        public boolean equals(Object obj) {
            GraphicalObj other = (GraphicalObj) obj;
            return topLeftX == other.topLeftX
                    && topLeftY == other.topLeftY
                    && height == other.height
                    && width == other.width
                    && color == other.color;
        }

        @Override
        public String toString() {
            return "Color(RGB) = " + red + ", " + green + ", " + blue +
                    "\nTop Left Point = (" + topLeftX +
                    ", " + topLeftY +
                    "), Height = " + height +
                    ", Width = " + width;
        }

        @Override
        public int compareTo(Object o) {
            if (this.topLeftX == (((GraphicalObj) o).topLeftX)       // if x, y, h, w is == and we already have that figure
                && this.topLeftY == (((GraphicalObj) o).topLeftY)    // we will not write the new obj in the collection
                && this.height == (((GraphicalObj) o).height)
                && this.width == (((GraphicalObj) o).width) )
                return 0;
            return 1;
        }


        public abstract double perimeter();
        public abstract double area();
    }


    class Rectangle extends GraphicalObj implements ICalc {

        public Rectangle() {
            super();
        }
        public Rectangle(long color, int topLeftX, int topLeftY, int height, int width) {
            super(color, topLeftX, topLeftY, height, width);
        }

        @Override
        public double perimeter() {
            return (height + width) * 2;
        }
        @Override
        public double area() {
            return (width * height);
        }

    }
    class Square extends GraphicalObj implements ICalc {

        public Square() {
            super();
        }
        public Square(long color, int topLeftX, int topLeftY, int height, int width) { // if width or height is not equal, it's a rectangle
            super(color, topLeftX, topLeftY, height, width);
        }

        @Override
        public double perimeter() {
            return (height + width) * 2;
        }

        @Override
        public double area() {
            return Math.pow(height, 2);
        }
    }
    class Circle extends GraphicalObj implements ICalc {

        public Circle() {
            super();
        }
        public Circle(long color, int topLeftX, int topLeftY, int height, int width) {  // if width is different from height, it's an oval
            super(color, topLeftX, topLeftY, height, width);
        }

        @Override
        public double perimeter() {
            return (2 * Math.PI * (height / 2.0));   // height / 2 == radius(r),
        }

        @Override
        public double area() {
            return (Math.PI * Math.pow((height / 2.0), 2));
        }
    }
    class Triangle extends GraphicalObj implements ICalc {

        public Triangle() {
            super();
        }
        public Triangle(long color, int topLeftX, int topLeftY, int height, int width) {
            super(color, topLeftX, topLeftY, height, width);
        }

        @Override
        public double perimeter() {
            double sides = Math.sqrt(Math.pow((width / 2.0), 2) + Math.pow(height, 2));
            return (width + (sides * 2));
        }

        @Override
        public double area() {
            return 0.5 * width * height;
        }
    }


    class FigureCollection implements IFile {
        protected Collection<GraphicalObj> tot = new ArrayList<>();

        protected String inputFile = "defaultIn.txt";
        protected String outputFile = "defaultOut.txt";

        public FigureCollection() { }
        public FigureCollection (String inputFile, String outputFile) {
            this.inputFile = inputFile;
            this.outputFile = outputFile;
            load();
        }

        @Override
        public void load() {
            try {
                // figureName color leftX leftY height width  -  all figures need these color, leftX, leftY, height, width parameters. We gotta make it clear to the program,
                // which parameter is whose(Class)
                Scanner in = new Scanner(new File(inputFile));
                String index;

                while (in.hasNext()) {
                    index = in.next();
                    switch (index) {
                        case "r":   // rectangle
                            Rectangle rect = new Rectangle(in.nextLong(), in.nextInt(), in.nextInt(), in.nextInt(), in.nextInt());
                            tot.add(rect);
                            break;
                        case "s":   // square
                            Square sqr = new Square(in.nextLong(), in.nextInt(), in.nextInt(), in.nextInt(), in.nextInt());
                            tot.add(sqr);
                            break;
                        case "c":   // circle
                            Circle cir = new Circle(in.nextLong(), in.nextInt(), in.nextInt(), in.nextInt(), in.nextInt());
                            tot.add(cir);
                            break;
                        case "t":   // triangle
                            Triangle tri = new Triangle(in.nextLong(), in.nextInt(), in.nextInt(), in.nextInt(), in.nextInt());
                            tot.add(tri);
                            break;
                        default:
                            break;
                    }
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
                if (tot.size() > 0) {
                    fout.setLength(0);
                }

                for (GraphicalObj cur : tot) {
                    fout.writeBytes(cur.getClass().getSimpleName().toLowerCase().charAt(0) + " ");   // to print what type the figure is - like the input file
                    fout.writeBytes(cur.color + " ");
                    fout.writeBytes(cur.topLeftX + " ");
                    fout.writeBytes(cur.topLeftY + " ");
                    fout.writeBytes(cur.height + " ");
                    fout.writeBytes(cur.width + "\r\n");
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

        @Override
        public void change(Object first, Object second) {
            if (tot.contains((GraphicalObj) first)) {
                tot.remove(first);
                tot.add((GraphicalObj) second);
            }
        }

        public void addFigure(Object obj) {
            tot.add((GraphicalObj) obj);
        }

        public void printSpecificFigures(Object c) {
            for (GraphicalObj graphicalObj : tot) {
                if (graphicalObj.getClass().equals(c.getClass()))
                    System.out.println(graphicalObj.toString());
            }
        }

        public void printAll() {
            for (GraphicalObj graphicalObj : tot) {
                System.out.println(graphicalObj.getClass().getSimpleName() + "\n" + graphicalObj.toString());
            }
        }

        public double totalPerimeters() {   // sum of all figures perimeter
            double result = 0.0;
            for (GraphicalObj graphicalObj : tot) {
                result += graphicalObj.perimeter();
            }
            return result;
        }

        public double totalArea() {   // sum of all figures area
            double result = 0.0;
            for (GraphicalObj graphicalObj : tot) {
                result += graphicalObj.area();
            }
            return result;
        }
    }


    public class Main {
        public static void main(String[] args) {
            Triangle tri_obj = new Triangle(0,0,0,0,0);  // default, for class name

            FigureCollection file = new FigureCollection("src/fileIn.txt", "src/fileOut.txt");
            System.out.println("Figures from the file:");
            file.printAll();

            Circle toChange = new Circle(256, 1, 1, 1, 23);  // the figure we want to replace
            Circle toAdd = new Circle(0, 1, 2, 3, 4);        // the new figure
            file.change(toChange, toAdd);
            System.out.println("\n\nAll the circles:");
            file.printSpecificFigures(toAdd); // printing "circles", to see that (1, 1, 1, 23) is removed and replaced with "toAdd"
            System.out.println("\n\n");

            Rectangle rect_obj = new Rectangle(255,3,2,12,3); // for adding a figure in the collection
            file.addFigure(rect_obj);
            System.out.println("\nAll the rectangles:");
            file.printSpecificFigures(rect_obj);  // printing "rectangles", to see that there are 3 rectangles (in the file we have 2)
            System.out.println("\n\n");

            System.out.println("\nAll the triangles:");
            file.printSpecificFigures(tri_obj);  // printing "triangles"

            System.out.println("\n\nTotal parameter: " + file.totalPerimeters());   // i've tested it with less figures, it works
            System.out.println("Total area: " + file.totalArea());                  // this works too

            file.save();
        }
    }
