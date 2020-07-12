# include<iostream>
# include<string>
# include<algorithm>
# include "fstream"
using namespace std;
struct actor {
	string actor_name;
	actor *next;
	actor *previous;
};
template<typename T>
struct node {
	string  movie_name;
	int year;
	int duration;
	actor *name;
	node *next;
	node *previous;
};
template<typename t>
class dLinkList {
	node<t> *head;
public:
	dLinkList();
	int lenght_actor(node<t> *&temp);///////////   done
	void display();////////    done
	void insertsorting(t m_name, int release, int time, int size);
	void insert_cast_sorting(node<t> *&temp, string cast);
	void add_actor(node<t> *&temp, int size);
	void display_actor(node<t> *&temp);
	void findMovie(string movie_name, node<t> *&temp);
	bool empty();///////       done
	void delete_Movie(string name);
	void delete_all_cast(node<t> *&temp);
	void delete_cast(node<t> *&temp, string cast);
	bool search_actor(node<t> *&temp, string cast);
	void Find_Movie_By_ActorName(string cast);
	void save_data();
	void Read_Data();
	void menu();
};
template<typename t>
bool dLinkList<t>::empty()
{
	if (head == nullptr)
		return true;
	return false;
}
template<typename t>
dLinkList<t>::dLinkList()
{
	head = nullptr;
}
template<typename t>
void dLinkList<t>::delete_Movie(string name)
{
	if (head == nullptr)
	{
		cout << "\nThere is no movie by this name.";
		return;
	}

	node<t> *temp = head;
	node<t>*itr = new node<t>;
	if (head->next == head)
	{
		head = nullptr;
		delete temp;
		temp = nullptr;
		return;
	}
	else if (head->movie_name == name)
	{
		itr = temp;
		itr = itr->previous;
		temp = temp->next;
		itr->next = temp;
		temp->previous = itr;
		itr = head;
		head = temp;
		delete itr;
		itr = nullptr;
		return;
	}
	else
	{
		while (true)
		{
			if (temp->movie_name == name)
			{
				itr = temp;
				itr = itr->previous;
				itr->next = temp->next;
				temp->next->previous = itr;
				delete temp;
				temp = nullptr;

				return;
			}
			if (temp->next == head)
				break;
			temp = temp->next;
		}
	}
	cout << "\nNo movie found by this name.";
}
template<typename t>
void dLinkList<t>::delete_all_cast(node<t> *&temp)
{
	if (temp->name == nullptr)
	{
		return;
	}
	actor *ptr = temp->name;
	actor *itr = ptr;
	itr = itr->previous;
	itr->next = nullptr;
	itr = ptr;
	while (ptr != nullptr)
	{
		ptr = ptr->next;
		itr = nullptr;
		delete itr;
		itr = ptr;
	}
	temp->name = nullptr;
}
template<typename t>
void dLinkList<t>::delete_cast(node<t> *&temp, string cast)
{
	actor *itr = new actor;
	actor *ptr = temp->name;
	if (ptr == nullptr)
	{
		cout << "\nThere is no data to delete.";
		return;
	}
	if (ptr->next == temp->name && ptr->actor_name == cast)
	{
		temp->name = nullptr;
		delete ptr;
		ptr = nullptr;
		return;
	}
	if (ptr->actor_name == cast)
	{
		actor *itr = ptr;
		itr = itr->previous;
		itr->next = ptr->next;
		ptr->next->previous = itr;
		free(ptr);
		ptr = nullptr;
		itr = itr->next;
		temp->name = itr;
		return;
	}
	while (true)
	{
		if (ptr->actor_name == cast)
		{
			itr = ptr;
			itr = itr->previous;
			itr->next = ptr->next;
			ptr->next->previous = itr;
			delete ptr;
			ptr = nullptr;
			return;
		}
		if (ptr->next == temp->name)
			break;
		ptr = ptr->next;
	}
	cout << "\n There is no Cast member by this name.";
}
template<typename t>
void dLinkList<t>::insert_cast_sorting(node<t> *&temp, string cast)
{
	actor *check = new actor;
	check->actor_name = cast; check->next = nullptr; check->previous = nullptr;
	if (temp->name == nullptr)
	{
		temp->name = check;
		temp->name->next = temp->name;
		temp->name->previous = temp->name;
	}
	else if (check->actor_name[0] <= temp->name->actor_name[0])
	{
		actor *ptr = new actor;
		ptr = temp->name;
		ptr = ptr->previous;
		check->next = temp->name;
		check->previous = ptr;
		ptr->next = check;
		temp->name->previous = check;
		temp->name = check;
	}
	else
	{
		actor *itr = temp->name;
		actor *ptr = new actor;
		while (check->actor_name[0] > itr->actor_name[0])
		{
			ptr = itr;
			itr = itr->next;
			if (check->actor_name[0] < itr->actor_name[0])
			{
				check->next = itr;
				itr->previous = check;
				ptr->next = check;
				check->previous = ptr;
				return;
			}
			if (itr->next == temp->name)
			{
				break;
			}
		}
		ptr = itr;
		itr = itr->next;
		ptr->next = check;
		check->previous = ptr;
		itr->previous = check;
		check->next = itr;
	}
}
template<typename t>
void dLinkList<t>::add_actor(node<t> *&temp, int size)
{
	string name;
	cin.ignore();
	for (int i = 0; i < size; i++)
	{
		cout << "Enter the name of the actor/actress: ";
		name.clear();
		getline(cin, name);
		insert_cast_sorting(temp, name);
	}
}
template<typename t>
void dLinkList<t>::insertsorting(t m_name, int release, int time, int size)
{
	node<t>*temp = new node<t>;
	temp->movie_name = m_name; temp->year = release; temp->duration = time; temp->next = nullptr; temp->previous = nullptr;
	temp->name = nullptr;
	if (size > 0)
		add_actor(temp, size);
	if (empty())
	{
		head = temp;
		head->next = head; head->previous = head;
	}
	else if (temp->movie_name[0] <= head->movie_name[0])
	{
		node<t>*ptr = new node<t>;
		ptr = head;
		ptr = ptr->previous;
		temp->next = head;
		temp->previous = ptr;
		ptr->next = temp;
		head->previous = temp;
		head = temp;
	}
	else
	{
		node<t>*itr = head;
		node<t>*ptr = new node<t>;
		while (temp->movie_name[0] > itr->movie_name[0])
		{
			ptr = itr;
			itr = itr->next;
			if (temp->movie_name[0] < itr->movie_name[0])
			{
				temp->next = itr;
				itr->previous = temp;
				ptr->next = temp;
				temp->previous = ptr;
				return;
				break;
			}
			if (itr->next == head)
			{
				break;
			}
		}
		ptr = itr;
		itr = itr->next;
		ptr->next = temp;
		temp->previous = ptr;
		itr->previous = temp;
		temp->next = itr;
	}

}
template<typename t>
void dLinkList<t>::findMovie(string movie_name, node<t> *&temp)
{
	node<t> *itr = head;
	while (true)
	{
		if (itr->movie_name == movie_name)
		{
			temp = itr;
			return;
		}
		else
			if (itr->next == head)
				break;
		itr = itr->next;

	}
	temp = nullptr;
	return;
}
template<typename t>
bool dLinkList<t>::search_actor(node<t> *&temp, string cast)
{
	if (temp->name == nullptr)
	{
		return false;
	}
	actor *ptr = new actor;
	ptr = temp->name;
	while (true)
	{
		if (ptr->actor_name == cast)
		{
			return true;
		}
		if (ptr->next == temp->name)
			break;
		ptr = ptr->next;
	}
	return false;
}
template<typename t>
void dLinkList<t>::Find_Movie_By_ActorName(string cast)
{
	int i = 0;
	if (head == nullptr)
	{
		cout << "There is no data to search from.";
		return;
	}
	node<t> *temp = head;
	while (true)
	{
		if (search_actor(temp, cast))
		{
			i++;
			cout << temp->movie_name;
			cout << "\nYear of release: " << temp->year;
			cout << "\nMovie lenght in minutes: " << temp->duration;
			cout << endl;
			display_actor(temp);
			cout << endl << "-------------------------------------------------------------\n";
		}
		if (temp->next == head)
			break;
		temp = temp->next;
	}
	if (i == 0)
	{
		cout << "\nThere is no movie by this actor name.";
	}
}
template<typename t>
void dLinkList<t>::menu()
{
	int n = 0; int option = 0;
	string moveName;
	int release, time, size;
	while (n != 10)
	{
		system("cls");
		cout << "\t\t\t\tMovie DataBase";
		cout << "\n\t\t\t Please select a number to perform \n \t\t\t\t your task.";
		cout << "\n 1)Add Movie. \n 2)Add Cast.\n 3)Delete Movie.\n 4)Delete Cast.\n 5)Find Movie.\n 6)Find Movies by Actor name.\n 7)Display Movies.\n 8)Save Data\n 9)Read Data\n 10)Exit";
		cout << "\nPick an option: "; cin >> n;

		if (n == 1)
		{
			//////////////ADDS MOVIES WITH CAST MEMBERS
			system("cls");
			cin.ignore();
			cout << "Enter movie name:"; getline(cin, moveName);
			cout << "Enter Year of release:"; cin >> release;
			cout << "Enter total duration of movie in Minites: "; cin >> time;
			cout << "Enter the number of cast members in this movie:"; cin >> size;
			insertsorting(moveName, release, time, size);
			system("cls");
			display();
		}
		else if (n == 2)
		{
			///////////////ADDS Cast members
			cin.ignore();
			system("cls");
			if (head == nullptr)
			{
				cout << "There is no data present.";
			}
			else
			{
				node<t> *temp = new node<t>;
				cout << "Enter the movie name in which you want to add cast members: "; getline(cin, moveName);
				findMovie(moveName, temp);
				if (temp == nullptr)
					cout << "No movie found.";
				else
				{
					cout << "Enter the number of cast members you want to enter."; cin >> size;
					add_actor(temp, size);
				}
			}
		}
		else if (n == 3)
		{
			///////////DELETES MOVIE
			system("cls");
			cin.ignore();
			if (head == nullptr)
			{
				cout << "There is no data present.";
			}
			else
			{
				node<t> *temp = new node<t>;
				cout << "Enter the Name of the movie you want to delete: "; getline(cin, moveName);
				findMovie(moveName, temp);
				if (temp == nullptr)
					cout << "No Movie present in records by this name.";
				else
				{
					delete_all_cast(temp);
					delete_Movie(moveName);
				}
			}
		}
		else if (n == 4)
		{
			////////////DELETES CAST MEMBER
			cin.ignore();
			system("cls");
			if (head == nullptr)
			{
				cout << "There is no data present.";
			}
			else
			{
				node<t> *ptr = new node<t>;
				cout << "\n Enter name of the movie from which you wish to delete a cast member: ";
				getline(cin, moveName);
				findMovie(moveName, ptr);
				if (ptr == nullptr)
				{
					cout << "\n There is no movie by the name you entered.";
				}
				else if (ptr != nullptr && ptr->movie_name == moveName)
				{
					cout << "\nEnter the name of the cast member: "; getline(cin, moveName);
					delete_cast(ptr, moveName);
				}
			}
		}
		else if (n == 5)
		{
			//////////FINDS MOVIE
			system("cls");
			if (head == nullptr)
			{
				cout << "There is no data present.";
			}
			else
			{
				cin.ignore();
				node<t> *temp = new node<t>;
				cout << "Enter the Movie you want to find: ";
				getline(cin, moveName);
				findMovie(moveName, temp);
				if (temp == nullptr)
					cout << "\nMovie not found.\n";
				else
				{
					cout << "Movie name: " << temp->movie_name;
					cout << "\nYear of release: " << temp->year;
					cout << "\nMovie lenght in minutes: " << temp->duration;
					cout << "\n";
					display_actor(temp);
					cout << endl << "-------------------------------------------------------------\n";
				}
			}
		}
		else if (n == 6)
		{
			//////Finds Movie by actor name
			system("cls");
			if (head == nullptr)
			{
				cout << "There is no data present.";
			}
			else
			{
				cin.ignore();
				cout << "Enter the name of the actor: ";
				getline(cin, moveName);
				Find_Movie_By_ActorName(moveName);
			}

		}
		else if (n == 7)
		{
			////////////Displays Data
			system("cls");
			display();
		}
		else if (n == 8)
		{
			////////////Saves Data in file
			if (head == nullptr)
			{
				cout << "There is no data To save.";
			}
			else
				save_data();
		}
		else if (n == 9)
		{
			///////Reads data from file
			Read_Data();
		}
		system("pause");
	}

}
template<typename t>
int dLinkList<t>::lenght_actor(node<t> *&temp)
{
	actor *ptr = temp->name;
	if (ptr == nullptr)
	{
		return 0;
	}
	else if (ptr->next == temp->name)
	{
		return 1;
	}
	else
	{
		int i = 1;
		for (; true; i++)
		{
			ptr = ptr->next;
			if (ptr->next == temp->name)
				break;
		}
		return i + 1;
	}
	return -1;
}
template<typename t>
void dLinkList<t>::display_actor(node<t> *&temp)
{
	if (lenght_actor(temp) != 0)
	{
		if (temp->name->next == temp->name)
		{
			cout << "Cast Names: \n" << temp->name->actor_name;
			return;
		}
		else
		{
			actor *check = temp->name;
			cout << "Cast Name: \n";
			while (true)
			{
				cout << check->actor_name << "\n";
				check = check->next;
				if (check->next == temp->name)
					break;
			}
			cout << check->actor_name;
		}
	}
}
template<typename t>
void dLinkList<t>::display()
{
	node<t>*temp = head;
	if (!(empty()))
	{
		if (head->next == head)
		{
			cout << "Movie name: " << head->movie_name;
			cout << "\nYear of release: " << head->year;
			cout << "\nMovie lenght in minutes: " << head->duration;
			cout << "\n";
			display_actor(temp);
			cout << endl << "-------------------------------------------------------------\n";

			return;
		}
		else
		{
			while (true)
			{
				cout << temp->movie_name;
				cout << "\nYear of release: " << temp->year;
				cout << "\nMovie lenght in minutes: " << temp->duration;
				cout << endl;
				display_actor(temp);
				cout << endl << "-------------------------------------------------------------\n";
				temp = temp->next;
				if (temp->next == head)
					break;
			}
			cout << temp->movie_name;
			cout << "\nYear of release: " << temp->year;
			cout << "\nMovie lenght in minutes: " << temp->duration;
			cout << endl;
			display_actor(temp);
			cout << endl << "-------------------------------------------------------------\n";
		}
	}
	else
	{
		cout << "No movie_name to display";
	}
}
template<typename t>
void dLinkList<t>::save_data()
{
	string name;
	node<t> *temp = head;
	ofstream fin;
	fin.open("movieRecords.txt");
	while (true)
	{
		fin << temp->movie_name << "\n";
		fin << temp->year << "\n";
		fin << temp->duration << "\n";
		fin << lenght_actor(temp) << "\n";
		actor *ptr = temp->name;
		for (int i = 0; i < lenght_actor(temp); i++)
		{
			fin << ptr->actor_name << "\n";
			ptr = ptr->next;
		}
		if (temp->next == head)
			break;
		temp = temp->next;
	}
	fin.close();
}
template<typename t>
void dLinkList<t>::Read_Data()
{
	node<t>* ptr = new node<t>;
	ifstream fin;
	fin.open("movieRecords.txt");
	string movie; int year; int duration; int size; string name;
	while (getline(fin, movie))
	{
		fin >> year;
		fin >> duration;
		fin >> size;
		insertsorting(movie, year, duration, 0);
		findMovie(movie, ptr);
		fin.ignore();
		for (int i = 0; i < size; i++)
		{
			getline(fin, name);
			insert_cast_sorting(ptr, name);
		}
		ptr = nullptr;
	}

}
int main()
{
	dLinkList<string>l;
	l.menu();
	return 0;
}