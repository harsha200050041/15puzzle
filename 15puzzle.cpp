#include <FL/Fl.H> // needed in every fltk program
#include <FL/Fl_Window.H> // needed to use the Fl_Window class
#include <FL/Fl_Button.H> // needed to use the Fl_Box class
#include <FL/Fl_Radio_Button.H> // needed to use the Fl_Box class
#include <FL/Fl_Light_Button.H> // needed to use the Fl_Box class
#include <cstdlib>
#include<time.h>

char *int2charstar (int v) {
 char *s = new char[sizeof(int)];
 sprintf(s,"%d",v);
 return s;
};


class MyButton : public Fl_Button {
	MyButton ** Button;
	public:
		MyButton (int x, int y, int w, int h, const char *l,MyButton ** button); 
		int handle(int e); // e is incoming mouse event of different kinds
		int index();
		bool gamestart();
 };

MyButton :: MyButton (int x,int y, int w, int h, const char *l,MyButton ** button) : Fl_Button (x,y,w,h,l) {
	Button=button;
}
int MyButton :: index() {int i;
	for(int j=0;j<16;j++) {if(this==Button[j]) i=j;}
	return i;
	};
	
int MyButton :: handle (int e) {
	if(e==FL_PUSH){if(index()!=0 && Button[index() -1]->label() == NULL) {Button[index() -1]->label(label());
	Button[index() -1]->color(FL_GREEN);
	label(NULL);this->color(FL_RED);}
	if(index()!=15 && Button[index() +1]->label() == NULL) {Button[index() +1]->label(label());Button[index() +1]->color(FL_GREEN);
	label(NULL);this->color(FL_RED);}
	if(index()>3 && Button[index() -4]->label() == NULL) {Button[index() -4]->label(label());Button[index() -4]->color(FL_GREEN);
	label(NULL);this->color(FL_RED);}
	if(index()<12 && Button[index() +4]->label() == NULL) {Button[index() +4]->label(label());Button[index() +4]->color(FL_GREEN);
	label(NULL);this->color(FL_RED);}}
	return 1;};
	
bool MyButton :: gamestart () {for(int j=0;j<16;j++){if(j!=index() && (atoi(Button[j]->label())==atoi(label()))) return false;}
			return true;};

int main(int argc, char *argv[]) {
    	Fl_Window *window;
    	srand(time(0));

window = new Fl_Window (600,600,"DEMO"); // outer window
	MyButton *button[16];
	int s;s=rand()%16;
	for (int i = 0; i < 16; i++) {
	button[i] = new MyButton (100*(1 + (i % 4)),100*(1 + (i / 4)),100,100,"b",button);
 	button[i]->label(int2charstar(s));
 	button[i]->color(FL_GREEN);
	}
	for(int i=0;i<16;i++) {while(!button[i]->gamestart()){int r;
	r=rand()%16;button[i]->label(int2charstar(r));}}
	for(int i=0;i<16;i++){button[i]->labelsize(40);
	if(atoi(button[i]->label())==0) {button[i]->label(NULL);
	button[i]->color(FL_RED);}}
	window->color(FL_WHITE);
	window->end();
    	window->show();
    	return(Fl::run());  // the process waits from here on for events
    }

