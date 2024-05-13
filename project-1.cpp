#include<iostream>
#include<string>
#include<vector>
#include<ctime>
#include<fstream>
#include <sstream>
#define SCISSORS 3
#define ROCK 1
#define PAPER 2
using namespace std;
void game() {
	int player_throw,ai_throw;
	char choice;
	do {
		cout<<"Enter your throw"<<endl;
		cout<<"1.ROCK\n2.PAPER\n3.SCISSORS"<<endl;
		cin>>player_throw;
		srand(time(NULL));
		ai_throw=rand()%3+1;
		cout<<"AI THROWS ";
		switch(ai_throw) {
			case 1:
				cout<<"ROCK"<<endl;
				break;
			case 2:
				cout<<"PAPER"<<endl;
				break;
			case 3:
				cout<<"SCISSORS"<<endl;
		}
		if(player_throw==ai_throw) {
			cout<<"ITS A DRAW"<<endl;
		} else if(ai_throw==SCISSORS && player_throw==PAPER) {
			cout<<"SCISSORS BEAT PAPER.YOU LOSE"<<endl;
		} else if(player_throw==SCISSORS && ai_throw==PAPER) {
			cout<<"SCISSORS BEAT PAPER.YOU WIN"<<endl;
		} else if(ai_throw==ROCK && player_throw==PAPER) {
			cout<<"PAPER BEATS ROCK.YOU LOSE"<<endl;
		} else if(player_throw==ROCK && ai_throw==PAPER) {
			cout<<"PAPER BEATS ROCK.YOU WIN"<<endl;
		} else if(ai_throw==ROCK && player_throw==SCISSORS) {
			cout<<"ROCK BEATS SCISSORS.YOU LOSE"<<endl;
		} else if(player_throw==ROCK && ai_throw==SCISSORS) {
			cout<<"ROCK BEATS SCISSORS.YOU WIN"<<endl;
		}
		cout<<"Enter Any Key To Continue OR Enter 1 To Exit"<<endl;
		cin>>choice;
	} while(choice!='1');
}
ofstream p("posts.txt",ios_base::app);
ofstream c("comments.txt",ios_base::app);

class Settings {
		int ch;
		friend class RegularUser;
		friend class BusinessUser;
		
	public:
		void display() {
			system("cls");
			cout << " 1. Chats\n 2.Posts\n 3.Game\n 4.User Data \n 5.Logout\n ";
			cin >> ch;
		}
		void displayfeed() {
			system("cls");
			cout << " 1. View Feed\n 2. Create Posts\n";
			cin >> ch;
		}
		void displaybfeed() {
			system("cls");
			cout << " 1. View Feed\n 2. Create Posts\n 3. Promote Post\n";
			cin >> ch;
		}
};

class User {
	protected:
		int userID;
		string username;
		string password;
		string email;
		vector<User> friendsList;

	public:
		User() {}
		User(int id, string un, string pw, string em)
			: userID(id), username(un), password(pw), email(em) {
			// Read friends list from file
			readFriendsListFromFile();
		}

		void readFriendsListFromFile() {
			string filename = username + "friendlist.txt";
			ifstream file(filename);
			if (file.is_open()) {
				string friendUsername;
				while (getline(file, friendUsername)) {
					// Create a temporary User object for each friend and add it to the friendsList
					friendsList.push_back(User(-1, friendUsername, "", ""));
				}
				file.close();
			} else {
				cout << "Unable to open file: " << filename << endl;
			}
		}

		void writeFriendsListToFile() {
			string filename = username + "friendlist.txt";
			ofstream file(filename, ios::app); // Append mode
			if (file.is_open()) {
				// Write the username of the new friend to the file
				for (auto& friendUser : friendsList) {
					file << friendUser.getUsername() << endl;
				}
				file.close();
			} else {
				//cout << "Unable to open file: " << filename << endl;
			}
		}

		int getUserId() {
			return userID;
		}

		string getUsername() {
			return username;
		}

		string getPassword() {
			return password;
		}

		string getEmail() {
			return email;
		}

		bool authenticate(string uName, string pWord) {
			return (username == uName && password == pWord);
		}

		bool login(string inputUsername, string inputPassword) {
			if (authenticate(username, password)) {
				cout << "Welcome back " << inputUsername << "!" << endl;
				return true;
			} else {
				return false;
			}
		}

		static User createAccount(int id, string un, string pw, string em) {
			return User(id, un, pw, em);
			cout << "User created!" << endl << endl;
		}

		void addFriend(User u) {
			friendsList.push_back(u);
			cout << u.getUsername() << " is now your friend!" << endl << endl;
			// Write the updated friends list to file
			writeFriendsListToFile();
		}

		void removeFriend(User u) {
			for (auto it = friendsList.begin(); it != friendsList.end(); ++it) {
				if (it->getUsername() == u.getUsername()) {
					friendsList.erase(it);
					break;
				}
			}
			cout << u.getUsername() << " was removed from your friend list." << endl << endl;
			// Write the updated friends list to file
			writeFriendsListToFile();
		}

		void displayFriendsList() {
			cout << "Friends List: " << endl;
			for (auto friendID : friendsList) {
				cout << "- " <<  friendID.getUsername() << endl;
			}
			cout << endl;
		}


		/* void updateSettings(Setting)
		 {
		     settings = newSettings;
		     cout << endl << "Settings are updated!" << endl;
		     cout << "New settings are: " << endl;
		     settings.displaySettings();
		 }*/

		void displayUserDetails() {
			cout << "User ID: " << userID << endl;
			cout << "Username: " << username << endl;
			cout << "Email: " << email << endl;
			displayFriendsList();
		}
};

template <typename T>
class Post {
	private:
		int postId;
		T content;
		int likes;
		int views;
		int numOfcomments;
		vector<string> comments;

	public:
		Post() {};
		Post(int id, string content)
			: postId(id), content(content), likes(0), views(0), numOfcomments(0)
		{};
		void addLikes() {
			likes++;
		}

		void addComments(string co) {

			comments.push_back(co);
			numOfcomments++;
			c.open("comments.txt",ios_base::app);
			c<<co<<endl;
			c.close();
		}

		void increaseViews(int v) {
			views += v;
		}

		int getLikes() {
			return likes;
		}

		int getViews() {
			return views;
		}

		int getNumOfcomments() {
			return numOfcomments;
		}

		void displayPostDetails() {
			cout << "Post ID: " << postId << endl;
			cout << "Content Of Post: " << content << endl;
			cout << "Likes Count: " << likes << endl;
			cout << "Views Count: " << views << endl;
			cout << "Comments count: " << numOfcomments << endl;
			cout << "Comments: " << endl;
			for (auto &cmnts : comments) {
				cout << cmnts;
			}
		}
		void addPost(string content,string file) {
			p.open("posts.txt",ios_base::app);
			ofstream userp(file,ios_base::app);
			p<<content<<endl;
			userp<<content<<endl;
			p.close();
		}
};

class message {
	private:

		string msg;
		time_t messageSent;
		time_t messageRead;

	public:
		User* sender;
		User* receiver;
		message() {}
		message(User *sender,User *receiver,string m):sender(sender),receiver(receiver) {
			msg = m;
			messageSent=time(nullptr);
		};
		void editMessage(string m) {
			msg = m;
			cout<<"The message has been edited "<<endl;
		}
		/*void unsendMessage() {
			cout<<"The message has been unsent "<<endl;
		}*/
		string getMessage() {
			return msg;
		}
		void displayMessage() {
			cout<<getMessage();
		}
		void mark_as_read() {
			messageRead=time(nullptr);
		}
		bool is_read() {
			return messageRead!=-1;
		}
		void writetochat(string f) {
			ofstream ofs(f);
			if (!ofs.is_open()) {
				cerr << "Error opening file for writing." << endl;
				return;
			}

			// Write each message to the file in the format: Sender,Receiver,Message
			ofs << sender->getUsername() << ",";
			ofs << receiver->getUsername() << ",";
			ofs << this->msg << endl;

			ofs.close();
		}
		~message() {
			delete receiver;
			delete sender;
		}
		friend ostream& operator<<(ostream& os, message& obj) {
			os << "\nSender: "<<obj.sender->getUsername()<<"\nReciever: "<<obj.receiver->getUsername()<<"\nMessage: "<< obj.msg;
			return os;
		}
};

class Chatp {
	public:
		vector<message> messages;
		Chatp() {}
		virtual void displaychat()=0;

};

class Chat : public Chatp {
	public:
		Chat() {}

		void readfromChat(const string& filename) {
			ifstream ifs(filename);
			try {
				if(ifs.is_open()) {
					ifs.close();
				} else {
					throw(505);
				}
			} catch(...) {
				cout << "\nUnable to open file for user. Information will not load. Plz exit and try again.";
			}
			if (!ifs.is_open()) {
				cerr << "Error opening file for reading." << endl;
				return;
			}

			string line;
			while (getline(ifs, line)) {
				// Each line represents a message in the format: Sender,Receiver,Message
				stringstream ss(line);
				string sender, receiver, msg;
				char delimiter = ',';
				getline(ss, sender, delimiter);
				getline(ss, receiver, delimiter);
				getline(ss, msg, delimiter);

				User* senderPtr = new User(10,sender," ggg"," uuu");
				User* receiverPtr = new User(11,receiver," jjj", " hhh");
				message m(senderPtr, receiverPtr, msg);
				messages.push_back(m);
			}

			ifs.close();
		}

		void addmsg(message m) {
			messages.push_back(m);
			string filename = m.sender->getUsername()+ m.receiver->getUsername() + ".txt";
			string filenamee = m.receiver->getUsername() + m.sender->getUsername() + ".txt";
			writetoChat(filenamee);
			writetoChat(filename);

		}

		void displaychat() {
			for(int i = 0; i < messages.size(); i++) {
				cout << messages[i];
			}
		}

		void writetoChat(string filename) {
			for (auto& msg : messages) {
				msg.writetochat(filename);
			}
		}
};

class BusinessUser : public User {
	protected:
		const int MAX_POSTS = 10;
		vector<Post<string> *> feed;
		int postCount;
		vector <Chat> chats;
		int ch, ch1;
		vector<Post<string>*> homepage;

	public:
		BusinessUser() {}
		BusinessUser(int id, string un, string pw, string em)
			: User(id, un, pw, em), postCount(0) {
			ifstream ifs(getUsername()+"chats.txt");
			try {
				if(ifs.is_open()) {
					ifs.close();
				} else {
					throw(505);
				}
			} catch(...) {
				cout << "\nUnable to open file for user. Information will not load. Plz exit and try again.";
			}
		}

		void promotePost(Post<string> *p) {
			if (postCount < MAX_POSTS) {
				feed.push_back(p);
				postCount++;
				p->increaseViews(3);
				cout << endl << "Post Promoted!" << endl;
			} else {
				cout << endl << "Feed Is Full" << endl;
			}
		}

		void displayuseroptions(Settings& s) {
			do {
				s.display();
				cout << "/n";
				this -> ch = s.ch;
				switch(ch) {
					case 1: {
						do {
							system("cls");
							BusinessUser x(90,"Bussinesssfriend","hello","frind@email");
							addFriend(x);
							displayFriendsList();
							cout <<"\nFor friend: "<<friendsList[0].getUsername();
							Chat a;

							createchat(a,friendsList[0]);
							//viewchat(a,friendsList[0]);
							cout<<"\nEnter any number to return to menu. Enter 3 to exit";
							cin >> ch1;
						} while(ch1!=3);
						break;
					}
					case 2: {
						do {
							system("cls");
							s.displaybfeed();
							ch1 = s.ch;
							switch(ch1) {
								case 1: {
									system("cls");
									Post<string> post1(1, "First post content");
									addToFeed(&post1);
									viewFeed();
									cout <<"\nEnd of feed";
									cout<<"\nEnter any number to return to post menu. Enter 3 to exit";
									cin >> ch1;
									break;
								}
								case 2: {
									system("cls");
									string content;
									cout<<"Enter content: ";
									cin.ignore();
									getline(cin,content);
									Post<string> newpost(2, content);
									homepage.push_back(&newpost);
									cout << "\nPost added to homepage";
									cout<<"\nEnter any number above 3 to return to post menu. Enter 3 to exit";
									cin >> ch1;
									break;
								}
								case 3: {
									system("cls");
									promotePost(homepage[0]);
									cout << "Promoted Post\n ";
									cout<<"\nEnter any number above 3 to return to post menu. Enter 3 to exit";
									cin >> ch1;
									break;
								}
								default: {
									cout<<"\nInvalid choice.";
									break;
								}
							}
						} while(ch!=1 && ch!=2 && ch!=3);
						break;
					}
					case 3: {
						game();
						cout<<"\nEnter any number greater than 5 to return to menu. Enter 1-5 to exit: ";
						cin >> ch;
						break;
					}

					case 4: {
						displayUserDetails();
						cout<<"\nEnter any number greater than 5 to return to menu. Enter 1-5 to exit: ";
						cin >> ch;
						break;
					}

					case 5: {
						return;
						break;
					}
				}
			}	while (ch!= 1 && ch != 2 && ch != 3 && ch != 4 && ch!= 5);
		}
		void viewchat(Chat c, User u) {
			string file=getUsername()+u.getUsername()+".txt";
			c.readfromChat(file);
		}

		int createchat(Chat c, User u) {
			chats.push_back(c);
			string file=getUsername()+u.getUsername()+".txt";
			ofstream ifs(file,ios::app);
			if(!ifs.is_open()) {
				cout << "Couldn't create chat.";
			}
			string mesg;
			cout<<"\nSend a message: ";
			cin.ignore();
			getline(cin,mesg);
			User x(10,getUsername()," ", " ");
			message n(&x,&u,mesg);
			c.addmsg(n);
			cout << "\nMessage is sent";
			//chats[chats.size()-1].displaychat();
			//viewchat(file);
			return 3;

		}
		
		void addToFeed(Post<string> *post) {
			feed.push_back(post);
			postCount++;
			cout << endl <<  "Post Added To The Feed" << endl;
		}
		void viewFeed() {
			for (auto post : feed) {
				post->displayPostDetails();
			}
		}
};

class RegularUser : public User {
		static const int MAX_FEED_SIZE = 10;
		vector<Post<string> *> feed;
		vector<Post<string> *> homepage;
		vector<Chat> chats;
		int postCount;
		int ch, ch1;

	public:
		RegularUser() {}
		RegularUser(int id, string un, string pw, string em)
			: User(id, un, pw, em), postCount(0) {
		}
		void displayuseroptions(Settings& s) {
			do {
				s.display();
				cout << "/n";
				this -> ch = s.ch;
				switch(ch) {
					case 1: {
						do {
							system("cls");
							RegularUser x(90,"friend1","hello","frind@email");
							addFriend(x);
							displayFriendsList();
							cout <<"\nFor friend: "<<friendsList[0].getUsername();
							Chat a;

							createchat(a,friendsList[0]);
							cout<<"\nEnter any number to return to chat menu. Enter 3 to exit";
							cin >> ch1;
						} while(ch!= 3);

						cout<<"\nEnter any number greater than 5 to return to menu. Enter 1-5 to exit: ";
						cin >> ch;
						break;
					}
					case 2: {
						do {
							system("cls");
							s.displayfeed();
							ch1 = s.ch;
							switch(ch1) {
								case 1: {
									system("cls");
									Post<string> post1(1, "First post content");
									addToFeed(&post1);
									viewFeed();
									cout <<"\nEnd of feed";
									cout<<"\nEnter any number to return to post menu. Enter 3 to exit";
									cin >> ch1;
									break;
								}
								case 2: {
									system("cls");
									string content;
									cout<<"Enter content: ";
									cin.ignore();
									getline(cin,content);
									Post<string> newpost(2, content);
									homepage.push_back(&newpost);
									cout << "\nPost added to homepage";
									cout<<"\nEnter any number greater than 2 to return to menu. Enter 2 to exit";
									cin >> ch1;
									break;
								}
							}
						} while(ch1!= 1 && ch!=2);
						cout<<"\nEnter any number greater than 5 to return to menu. Enter 1-5 to exit: ";
						cin >> ch;
						break;
					}
					case 3: {
						game();
						cout<<"\nEnter any number greater than 5 to return to menu. Enter 1-5 to exit: ";
						cin >> ch;
						break;
					}

					case 4: {
						displayUserDetails();
						cout<<"\nEnter any number greater than 5 to return to menu. Enter 1-5 to exit: ";
						cin >> ch;
						break;
					}

					case 5: {
						return;
						break;
					}
				}
			}	while (ch!= 1 && ch != 2 && ch != 3 && ch != 4 && ch != 5);
		}
		void viewchat(string fil) {
			Chat c;
			c.readfromChat(fil);
		}

		void createchat(Chat c, User u) {
			chats.push_back(c);
			string file=getUsername()+u.getUsername()+".txt";
			ofstream ifs(file,ios::app);
			if(!ifs.is_open()) {
				cout << "Couldn't create chat.";
			}
			string mesg;
			cout<<"\nSend a message: ";
			cin.ignore();
			getline(cin,mesg);
			User x(10,getUsername()," ", " ");
			message n(&x,&u,mesg);
			c.addmsg(n);
			cout << "\nMessage is sent";
			//chats[chats.size()-1].displaychat();
			//viewchat(file);
			return;

		}
		void addToFeed(Post<string> *post) {
			if (postCount < MAX_FEED_SIZE) {
				feed.push_back(post);
				postCount++;
				cout << endl <<  "Post Added To The Feed" << endl;
			} else {
				cout << endl << "Feed is Full" << endl;
			}
		}
		void viewFeed() {
			for (auto post : feed) {
				post->displayPostDetails();
			}
		}
};

bool operator==(User u1,User u2) {
	return u1.getUsername()==u2.getUsername();
}

class Group {
	private:
		vector <RegularUser> users;
		string groupName;

	public:
		Group(string name) : groupName(name) {};
		void set_name(string name) {
			groupName=name;
		}

		void add_member(RegularUser member) {
			users.push_back(member);
			cout << endl <<  member.getUsername() << " has been added to the group "<< groupName <<endl;
		}

		void remove_member(RegularUser member) {
			for (auto i = users.begin(); i != users.end(); ) {
				if (*i == member) {
					i = users.erase(i);
				} else {
					++i;
				}
			}
		}
		void display_members() {
			for(int i=0; i<users.size(); i++) {
				cout<<users[i].getUsername()<<endl;
			}
		}
};

class Admin {
	private:
		Settings set;
		vector<RegularUser> regularUsers;
		vector<BusinessUser> businessUsers;

	public:
		Admin() {
			deserializeRegularUsers("regularuser.txt");
			deserializeBusinessUsers("businessuser.txt");
		}

		void deserializeRegularUsers(const string& filename) {
			ifstream ifs(filename);
			if (!ifs.is_open()) {
				cerr << "Error opening file for reading: " << filename << endl;
				return;
			}

			string line;
			while (getline(ifs, line)) {
				// Each line represents a full RegularUser object in the format: ID,Username,Password,Email
				stringstream ss(line);
				int id;
				string username, password, email;
				char delimiter = ',';
				getline(ss, line, delimiter);
				id = stoi(line);
				getline(ss, username, delimiter);
				getline(ss, password, delimiter);
				getline(ss, email, delimiter);

				RegularUser regUser(id, username, password, email);
				regularUsers.push_back(regUser);
			}

			ifs.close();
		}

		void serializerUsers(const string& filename) {
			ofstream ofs(filename);
			if (!ofs.is_open()) {
				cerr << "Error opening file for writing." << endl;
				return;
			}

			for ( auto& user : regularUsers) {
				// Each line represents a full RegularUser object in the format: ID,Username,Password,Email
				ofs << user.getUserId() << "," << user.getUsername() << "," << user.getPassword() << "," << user.getEmail() << endl;
			}

			ofs.close();
		}
		void deserializeBusinessUsers(const string& filename) {
			ifstream ifs(filename);
			if (!ifs.is_open()) {
				cerr << "Error opening file for reading: " << filename << endl;
				return;
			}

			string line;
			while (getline(ifs, line)) {
				// Each line represents a full BusinessUser object in the format: ID,Username,Password,Email
				stringstream ss(line);
				int id;
				string username, password, email;
				char delimiter = ',';
				getline(ss, line, delimiter);
				id = stoi(line);
				getline(ss, username, delimiter);
				getline(ss, password, delimiter);
				getline(ss, email, delimiter);

				BusinessUser busUser(id, username, password, email);
				businessUsers.push_back(busUser);
			}

			ifs.close();
		}

		void serializebUsers(const string& filename) {
			ofstream ofs(filename);
			if (!ofs.is_open()) {
				cerr << "Error opening file for writing." << endl;
				return;
			}

			for (auto& user : businessUsers) {
				ofs << user.getUserId() << "," << user.getUsername() << "," << user.getPassword() << "," << user.getEmail() << endl;
			}

			ofs.close();
		}

		void displaymainmenu() {
			system("cls");
			int ch;
			do {
				cout << "MSF SOCIAL SERVICES:\n 1.Login\n 2.Sign Up\n 3.Exit" << endl;
				cin >> ch;
				switch (ch) {
					case 1:
						int ch2;
						do {
							system("cls");
							cout << "Login for: \n 1.Regular User\n 2.Business User\n 3.Return to Main Menu\n";
							cin >> ch2;
							switch (ch2) {
								case 1: {
									string usern, userp;
									bool flag = 0;
									cout << "Enter username: ";
									cin.ignore();
									getline(cin, usern);
									cout << "Enter password: ";
									getline(cin, userp);
									for(int i = 0; i<regularUsers.size(); i++) {
										if(regularUsers[i].login(usern,userp)) {
											flag = 1;
											regularUsers[i].displayuseroptions(set);
											break;
										}
									}
									if(!flag) {
										cout << "\nUser not found. Returning to main menu.";
									}
									ch = 4;
									break;
								}
								case 2: {
									string usern, userp;
									bool flag = 0;
									do {
										cout << "Enter username: ";
										cin.ignore();
										getline(cin, usern);
										cout << "Enter password: ";
										getline(cin, userp);
										for(int i = 0; i<businessUsers.size(); i++) {
											if(businessUsers[i].login(usern,userp)) {
												flag = 1;
												break;
											}
											if(!flag) {
												cout << "\nUser not found. Returning to main menu.";
											}

										}
									} while(!flag);
									break;
								}
								case 3: {
									ch = 4;
									break;
									system("cls");
								}
								default: {
									cout << "Invalid choice for user type. Please enter 1 or 2." << endl;
									break;
								}
							}
						} while(ch2 != 1 && ch2!= 2 && ch2 != 3);
						break;
					case 2: {
						int ch3;
						do {
							system("cls");
							cout << "Sign Up for: \n 1.Regular User\n 2.Business User\n 3.Return to Main Menu\n";
							cin >> ch3;
							switch (ch3) {
								case 1: {
									string usern, userp, email;
									cout << "Enter username: ";
									cin.ignore();
									getline(cin, usern);
									cout << "Enter password: ";
									getline(cin, userp);
									cout << "Enter email: ";
									getline(cin, email);
									RegularUser newUser(regularUsers.size() + 1, usern, userp, email);
									regularUsers.push_back(newUser);
									cout << "Regular User Sign Up Successful!" << endl;
									serializerUsers("regularuser.txt");

									ch = 4;
									break;
								}
								case 2: {
									string usern, userp, email;
									cout << "Enter username: ";
									cin.ignore();
									getline(cin, usern);
									cout << "Enter password: ";
									getline(cin, userp);
									cout << "Enter email: ";
									getline(cin, email);
									BusinessUser newUser(businessUsers.size() + 1, usern, userp, email);
									businessUsers.push_back(newUser);

									cout << "Business User Sign Up Successful!" << endl;
									serializebUsers("businessuser.txt");
									ch = 4;
									break;
								}
								case 3: {
									break;
									system("cls");
								}
								default: {
									cout << "Invalid choice for user type. Please enter 1 or 2." << endl;
									break;
								}
							}
						} while (ch3 != 3);
						break;
					}
					case 3: {
						cout << "Exiting.....";
						return;
					}
					default: {
						cout << "Invalid choice. Please enter a valid option." << endl;
						system("cls");
						break;
					}
				}
			} while (ch != 1 && ch != 2 && ch != 3);


		}
};

int main() {
	Admin admin;
	admin.displaymainmenu();

	//EXAMPLE INSTANCES

	// Create regular user and business user
	RegularUser regularUser1(101, "user1", "userpass", "user1@example.com");
	BusinessUser businessUser1(201, "business1", "businesspass", "business1@example.com");

	// Authenticate users
	bool regularUserAuthenticated = regularUser1.authenticate("user1", "userpass");
	bool businessUserAuthenticated = businessUser1.authenticate("business1", "businesspass");
	cout << "Regular user authentication: " << regularUserAuthenticated << endl;
	cout << "Business user authentication: " << businessUserAuthenticated << endl;

	// Login users
	regularUser1.login("user1", "userpass");

	// Create posts
	Post<string> post1(1, "First post content");
	Post<string> post2(2, "Second post content");
	Post<string> post3(3, "Third post content");

	// Add likes to posts
	post1.addLikes();
	post2.addLikes();
	post3.addLikes();
	// Add comments to posts
	post1.addComments("Comment 1 on post 1");
	post1.addComments("Comment 2 on post 1");
	post2.addComments("Comment 1 on post 2");
	// Increase views of posts
	post1.increaseViews(10);
	post2.increaseViews(5);
	post3.increaseViews(8);

	// Display post details
	post1.displayPostDetails();
	post2.displayPostDetails();
	post3.displayPostDetails();

	// Promote posts for business user
	businessUser1.promotePost(&post1);
	businessUser1.promotePost(&post2);
	businessUser1.promotePost(&post3);

	// Add posts to regular user's feed
	regularUser1.addToFeed(&post1);
	regularUser1.addToFeed(&post2);
	regularUser1.addToFeed(&post3);

	// View regular user's feed
	regularUser1.viewFeed();

	// Create group
	Group group1("Group 1");

	// Add regular user to group
	group1.add_member(regularUser1);

	// Remove regular user from group
	group1.remove_member(regularUser1);

	// Display group members
	group1.display_members();

	// Create message
	message msg1(&regularUser1, &businessUser1, "Hello, business user!");

	//Edit message
	msg1.editMessage("Hi, business user!");

	// Display message
	msg1.displayMessage();

	// Mark message as read
	msg1.mark_as_read();

	// Check if message is read
	bool isMessageRead = msg1.is_read();
	cout << "Is message read? " << isMessageRead << endl;

	// Add friends
	RegularUser safia(99,"safia","safia.com","hihihellojee");
	regularUser1.addFriend(safia);

	// Remove friend
	regularUser1.removeFriend(safia);

	// Create account

	User newUser = User::createAccount(102, "newuser", "newpass", "newuser@example.com");
	post1.addPost("First post content",0);
	post2.addPost("Second post content",0);
	post3.addPost("Third post content",0);
	return 0;
}