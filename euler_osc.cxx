#include <iostream>
#include <cmath>
#include <fstream> //to print in file

using namespace std;

void backwardEule(double*, const double, const int);
void forwardEule(double*, const double, const int);

int main(){
    const double dt=M_PI/100.0;
    const double interval=20*M_PI;
    const int N=(interval/dt)+1; //Anzahl der Schritte
    
    double y[2]; //y[0] speichert die Lösungen für y1; y[1] für y2
        
    
    const double dtanalytisch=M_PI/100; //damit wir hier immer die richtige Lösung bekommen
    const int Nanalytisch=20*M_PI/dtanalytisch +1;
    
    forwardEule(y, dt, N);
    
    backwardEule(y, dt, N);
    
    // Analytische Lösung
    ofstream Eulera ("analytisch.dat");
    for (int i=0; i<Nanalytisch;i++){
        Eulera<<i*dtanalytisch<<"\t"<<cos(i*dtanalytisch)<<endl;
        }
    Eulera.close();
    
    
 return 0;
}

void forwardEule(double* y, const double dt, const int N){
    
    double y1temp=1; //Anfangsbedingung für y1(0) (also x(0))
    double y2temp=0; //Anfangsbedingung für y2(0) (also xpunkt(0))
    
    ofstream Eulerf ("forwardEule.dat");
    Eulerf<< 0 <<"\t"<<y1temp<<endl; //Anfangsbedingung in die Datei schreiben
    
    
    for (int i=0; i<(N-1); i++){ //wir berechnen den N+1ten Wert im letzten Schleifendurchgang!
    
        y[0]= y1temp+y2temp*dt;
        y[1]= y2temp-y1temp*dt;
        
        y1temp=y[0];
        y2temp=y[1];
        
        Eulerf<< (i+1)*dt<<"\t"<<y[0]<<endl; // Lösung für x ist in y1 gespeichert
    }  
         
    Eulerf.close();
}

void backwardEule(double* y, const double dt, const int N){
    
    double y1temp=1; //Anfangsbedingung für y1(0) (also x(0))
    double y2temp=0; //Anfangsbedingung für y2(0) (also xpunkt(0))
    
    ofstream Eulerb ("backwardEule.dat");
    Eulerb<< 0 <<"\t"<<y1temp<<endl; //Anfangsbedingung in die Datei schreiben
    
    for (int i=0; i<(N-1); i++){
        
        y[0]= (y1temp+y2temp*dt)/(1+dt*dt); //Gleichungssystem vorher nach y_n+1 auflösen
        y[1]= y2temp-(y1temp+dt*y2temp)*dt/(1+dt*dt);
        
        y1temp=y[0];
        y2temp=y[1];
        
        Eulerb<< (i+1)*dt<<"\t"<<y[0]<<endl;
    }  
    
    Eulerb.close();
}