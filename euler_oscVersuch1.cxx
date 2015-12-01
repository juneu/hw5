#include <iostream>
#include <cmath>
#include <fstream> //to print in file

using namespace std;

void backwardEule(double*, const double, const int);
void forwardEule(double*, const double, const int);

int main(){
    const double dt=M_PI/10.0;
    const double interval=20*M_PI;
    const int N=(interval/dt)+1; //Anzahl der Schritte
    
    double yF[2*N]; //y[0 bis N-1] speichert die Lösungen für y1; y[N bis 2*N-1] für y2
    double yB[2*N];
    
    forwardEule(yF, dt, N);
    backwardEule(yB, dt, N);
    

    
    ofstream Eulerf ("forwardEule.dat");
    ofstream Eulerb ("backwardEule.dat");
    ofstream Eulera ("analytisch.dat");
    
    for (int i=0; i<N;i++){
        Eulerf<< i*dt<<"\t"<<yF[i]<<endl; // Lösung für x ist in y1 gespeichert
        Eulerb<< i*dt<<"\t"<<yB[i]<<endl;
        Eulera<<i*dt<<"\t"<<cos(i*dt)<<endl;
        }
        
    Eulerf.close();
    Eulerb.close();
    Eulera.close();
    
    
 return 0;
}

void forwardEule(double* y, const double dt, const int N){
    y[0]=1; //Anfangsbedingung für y1(0) (also x(0))
    y[N]=0; //Anfangsbedingung für y2(0) (also xpunkt(0))
    
    for (int i=0; i<(N-1); i++){ // bis N-1 und nicht bis N, weil wir i+1 im letzten Schleifendurchgang berechnen
        
        y[i+1]= y[i]+y[i+N]*dt;
        y[i+N+1]= y[i+N]-y[i]*dt;
        
    }  
}

void backwardEule(double* y, const double dt, const int N){
    y[0]=1; //Anfangsbedingung für y1(0) (also x(0))
    y[N]=0; //Anfangsbedingung für y2(0) (also xpunkt(0))
    
    for (int i=0; i<(N-1); i++){
        
        y[i+1]= (y[i]+y[i+N]*dt)/(1+dt*dt); //Gleichungssystem vorher nach y_n+1 auflösen
        y[i+N+1]= y[i+N]-(y[i]+dt*y[i+N])*dt/(1+dt*dt);
        
    }  
}