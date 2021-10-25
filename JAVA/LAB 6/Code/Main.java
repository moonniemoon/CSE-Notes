				import java.util.List;
				import java.io.File;
				import java.io.FileNotFoundException;
				import java.io.IOException;
				import java.io.RandomAccessFile;
				import java.util.ArrayList;
				import java.util.Collection;
				import java.util.Collections;
				import java.util.Comparator;
				import java.util.Iterator;
				import java.util.Scanner;
				
				interface IEmail{
					public int compareToId(String id);
					public int compareToMessage(String message);
				}
				
				interface iPost{
					public void send_msg(String compose);
					public void get_msg(String getMsg);
				}
				
				interface IOinterface{
					public void read_msg();
					public void write_msg();
				}
				
				abstract class eMail_Message{
					protected String str_eMailMessage;
					
					public eMail_Message(){
						str_eMailMessage = "N/A";
					}
					public eMail_Message(String given_str){
						str_eMailMessage = given_str;
					}
					
					abstract void setEMailMessage(String msg); 	// �y�x�����p���p�~�u �~�p �������q���u�~�y�u
					abstract String getEMailMessage(); 			// �����|�����p�r�p�~�u �~�p �������q���u�~�y�u
				}
				
				class sorting_id implements Comparator<Object>{
					@Override
					public int compare(Object arg0, Object arg1) {
						return ((eMail_impl)arg0).compareToId(((eMail_impl)arg1).identification);
					}
				}
				class sorting_message implements Comparator<Object>{
					@Override
					public int compare(Object arg0, Object arg1) {
						return ((eMail_impl)arg0).compareToMessage(((eMail_impl)arg1).str_eMailMessage);
					}
				}
				
				class PostBox implements iPost{
					
					protected Collection<eMail_impl> inColl;
					protected Collection<eMail_impl> outColl;
					
					public PostBox() {
						inColl = new ArrayList<eMail_impl>();
						outColl = new ArrayList<eMail_impl>();
					}
					
					public Collection<eMail_impl> getIn() {
						return inColl;
					}
					public Collection<eMail_impl> getOut() {
						return outColl;
					}
				
					public List<eMail_impl> providerIDsort() {
						List<eMail_impl> temp = new ArrayList<eMail_impl>();
						temp.addAll(inColl);
						Collections.sort(temp, new sorting_id());
						return temp;
					}
					public List<eMail_impl> messageSort() {
						List<eMail_impl> temp = new ArrayList<eMail_impl>();
						temp.addAll(inColl);
						Collections.sort(temp,new sorting_message());
						return temp;
					}
					
					public void fillOut(Collection<eMail_impl> fromColl) {
						outColl.addAll(fromColl);
					}
					
					@Override
					public void send_msg(String compose) {
						try {
							RandomAccessFile fout = new RandomAccessFile(compose, "rw");
							for(Iterator<eMail_impl> It = inColl.iterator(); It.hasNext();) {
								eMail_impl current = (eMail_impl)It.next();
								fout.writeBytes(current.toString()+"\r\n");
							}
							fout.close();
						} catch (FileNotFoundException e) {
							e.printStackTrace();
						} catch (IOException e) {
							e.printStackTrace();
						}
					}
				
					@Override
					public void get_msg(String getMsg) {
						try {
							Scanner iStream = new Scanner(new File(getMsg));
							while(iStream.hasNext()) {
								eMail_impl single_row = new eMail_impl(iStream.next());
								inColl.add(single_row);
							}
							iStream.close();
						} catch (FileNotFoundException e) {
							e.printStackTrace();
						}
					}
					
				}
				
				public class eMail_impl extends eMail_Message implements IEmail,Comparable {
				
					protected int number;
					protected String identification;
					protected String mail_provider;
					protected String partial_msg;
					
					public eMail_impl(int nmb, String id, String prov, String msg) {
						number = nmb;
						identification = id;
						mail_provider = prov;
						str_eMailMessage = msg;
					}
					
					public eMail_impl(String complete_msg) {
						int i = 0;
						char temp_char;
						String temp_string = "";
						
						while(i < complete_msg.length()-1) {
							temp_char = complete_msg.charAt(i);
							i++;
							temp_string+=temp_char;
							
							if (complete_msg.charAt(i) == '-') {
								number = Integer.parseInt(temp_string);
								temp_string = "";
								i++;
							}
							if (complete_msg.charAt(i) == '@') {
								identification = temp_string;
								temp_string = "";
								i++;
							}
							if (complete_msg.charAt(i) == ':') {
								mail_provider = temp_string;
								temp_string = "";
								i+=2;
							}
						}
						temp_char = complete_msg.charAt(i);
						temp_string+=temp_char;
						partial_msg = temp_string;
					}
					
					public int get_number() {
						return number;
					}
					public String get_identification() {
						return identification;
					}
					public String get_provider() {
						return mail_provider;
					}
					public String get_partmessage() {
						return partial_msg;
					}
					
					public static void main(String[] args) {
						eMail_impl temp = new eMail_impl("1-name1@yahoo.com:=abcd trs bak");
						System.out.println(temp.number+"\n");
						System.out.println(temp.identification+"\n");
						System.out.println(temp.mail_provider+"\n");
						System.out.println(temp.str_eMailMessage+"\n");
				
					}
				
					@Override
					public int compareTo(Object arg0) {
						// TODO Auto-generated method stub
						return 0;
					}
				
					@Override
					public int compareToId(String id) {
						return this.identification.compareTo(id);
					}
				
					@Override
					public int compareToMessage(String message) {
						return this.str_eMailMessage.compareTo(message);
					}
				
					@Override
					void setEMailMessage(String msg) {
						// TODO Auto-generated method stub
						
					}
				
					@Override
					String getEMailMessage() {
						// TODO Auto-generated method stub
						return null;
					}
				
				}
