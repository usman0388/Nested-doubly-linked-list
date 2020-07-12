# Nested-doubly-linked-list
The given code has two nodes one for movies and the other for actors. Like:
struct actor {
	string actor_name;
	actor *next;
	actor *previous;
};
struct node {
	string  movie_name;
	int year;
	int duration;
	actor *name;
	node *next;
	node *previous;
};
Note that the node is considerd as "movie".
