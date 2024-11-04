#include "Graph.h"
#include "Node.h"
#include "Location.h"
#include "Path.h"
#include "Intersection.h"




int main()
{
    /*
    Location a("Bulevar");
    Location d("Parking");
    Path b("M54", 4, 5, 3);
    Path f("T4", 30, 20, 4);
    Intersection c("Kruzni_tok", 4, 5);
    Path g("Noo", 56, 45, 5);
    Intersection s("Kikiriki", 5, 5);
    Location h("Opstina");
    //Node a("M54");
    Graph mapa;
    //std::cout << c.Node_name()<<std::endl;
    mapa.add_Node(&a);
    mapa.add_Node(&b);
    mapa.add_Node(&c);
    mapa.add_Node(&d);
    mapa.add_Node(&f);
    //mapa.print();
    //mapa.find(&b);
    mapa.add_connection(&b, &c);
    mapa.add_connection(&a, &b);
    mapa.add_connection(&d, &c);
    mapa.add_connection(&c, &f);
    mapa.add_connection(&c, &a);
    mapa.add_connection(&f, &d);
    c.add_transition(3, 0,10);
    c.add_transition(1, 0,15);
    c.add_transition(1, 4,5);
    //c.ispisi();
    //mapa.add_connection(&a, &d);
    //mapa.ispisi();
    //c.printt();
    mapa.stef_ser("Stef.txt");
    mapa.serialize("Proba.txt");
    Graph mm;
    mm.deserialize("Proba.txt");
    mm.add_Node(&g);
    mm.add_connection("Bulevar", &g);
    mm.add_connection(&g, "Parking");
    mm.add_Node(&s);
    mm.add_connection("M54", "Kikiriki");
    mm.add_connection("T4", "Kikiriki");
    mm.add_connection("Kikiriki", "Parking");
    s.add_transition(1, 3, 8);
    s.add_transition(4, 3, 12);
    mm.add_Node(&h);
    mm.add_connection( "Opstina", "T4");
    //mm.add_connection("Bulevar", "Parking");
    //mm.add_connection(&g, &d);
    //mm.print();
    mm.serialize("Temp.txt");
    Vehicle k("BMW", 80);
    mm.add_vehicle(k);
    Vehicle j("Audi", 75);
    mm.add_vehicle(j);
    //mm.print_veh();
    mm.min_dist(k, "Bulevar", "T4");
    mm.min_time(k, "Bulevar", "Parking");
    mm.min_dist(j,  "Opstina","Parking");
    Graph stef;
    stef.stef_deser("Stef.txt");
    stef.stef_ser("Stefclone.txt");
    */

    Graph Traffic;
    Traffic.add_Node(new Location("Kuca"));//0
    Traffic.add_Node(new Location("Posao"));//1
    Traffic.add_Node(new Location("Kafic"));//2
    Traffic.add_Node(new Location("Fakultet"));//3
    Traffic.add_Node(new Location("Banka"));//4
    Traffic.add_Node(new Location("Market"));//5
    Traffic.add_Node(new Path("Kozarska",24,60,15));//6
    Traffic.add_Node(new Path("Majevicka",60,80,20));//7
    Traffic.add_Node(new Path("Autoput",100,120,40));//8
    Traffic.add_Node(new Path("Kninska",30,40,7));//9
    Traffic.add_Node(new Path("Patre",14,50,8));//10
    Traffic.add_Node(new Path("Banjalucka",28,50,12));//11
    Traffic.add_Node(new Path("Kralja_Petra",6,10,3));//12
    Traffic.add_Node(new Path("Savska",20,40,9));//13
    Traffic.add_Node(new Path("Prvomajska",50,40,8));//14
    Traffic.add_Node(new Path("Jovan_Ducic",32,30,7));//15
    Traffic.add_Node(new Path("Dunavska",12,30,6));//16
    Traffic.add_Node(new Path("Ruski_put",46,30,12));//17
    
    Intersection a = Intersection("Kruzni_tok", 10, 25);
    Intersection b = Intersection("Raskrsnica", 5, 35);
    Intersection c = Intersection("Petlja", 40, 40);
    Traffic.add_Node(&a);//18
    Traffic.add_Node(&b);//19
    Traffic.add_Node(&c);//20
    Traffic.add_Node(new Location("Granica"));//21
    Traffic.add_Node(new Path("Kralja_Alfonsa",18,30,7));//22
    Traffic.add_Node(new Path("Beogradska", 22, 30, 4));//23
    Traffic.add_connection("Kuca", "Kozarska");
    Traffic.add_connection("Kozarska", "Kruzni_tok");
    Traffic.add_connection("Kruzni_tok", "Majevicka");
    Traffic.add_connection("Kruzni_tok", "Kninska");
    Traffic.add_connection("Majevicka", "Posao");
    Traffic.add_connection("Kruzni_tok", "Autoput");
    Traffic.add_connection("Autoput", "Petlja");
    Traffic.add_connection("Kruzni tok", "Kninska");
    Traffic.add_connection("Kninska", "Kuca");
    Traffic.add_connection("Raskrsnica", "Beogradska");
    Traffic.add_connection("Beogradska", "Banka");
    Traffic.add_connection("Posao", "Patre");
    Traffic.add_connection("Patre", "Petlja");
    Traffic.add_connection("Petlja", "Banjalucka");
    Traffic.add_connection("Banjalucka", "Fakultet");
    Traffic.add_connection("Fakultet", "Kralja_Petra");
    Traffic.add_connection("Kralja_Petra", "Raskrsnica");
    Traffic.add_connection("Banka", "Savska");
    Traffic.add_connection("Savska", "Kruzni_tok");
    Traffic.add_connection("Raskrsnica", "Prvomajska");
    Traffic.add_connection("Prvomajska", "Market");
    Traffic.add_connection("Market", "Jovan_Ducic");
    Traffic.add_connection("Jovan_Ducic", "Raskrsnica");
    Traffic.add_connection("Petlja", "Ruski_put");
    Traffic.add_connection("Ruski_put", "Raskrsnica");
    Traffic.add_connection("Petlja", "Dunavska");
    Traffic.add_connection("Dunavska", "Granica");
    Traffic.add_connection("Kruzni_tok", "Kralja_Alfonsa");
    Traffic.add_connection("Kralja_Alfonsa", "Kafic");
    
    a.add_transition(6, 7, 10);
    a.add_transition(6, 8, 15);
    a.add_transition(13, 8, 10);
    a.add_transition(13, 7, 5);
    a.add_transition(13, 9, 10);
    b.add_transition(17, 23, 15);
    b.add_transition(17, 14, 20);
    b.add_transition(12, 23, 12);
    b.add_transition(12, 14, 15);
    b.add_transition(15, 23, 10);
    c.add_transition(8, 16, 5);
    c.add_transition(8, 11, 10);
    c.add_transition(8, 17, 15);
    c.add_transition(10, 17, 5);
    c.add_transition(10, 11, 10);
    c.add_transition(10, 16, 15);
    Vehicle v("BMW", 150);
    Traffic.add_vehicle(v);
    Traffic.min_dist(v, "Fakultet", "Granica");
    Traffic.min_time(v, "Fakultet", "Granica");
    
    Traffic.list_ser("LL.txt");
    Traffic.serialize("Le.txt");
    return 0;

}