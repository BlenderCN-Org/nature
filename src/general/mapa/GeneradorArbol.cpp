#include "GeneradorArbol.h"


Arbol GeneradorArbol::generarArbol(float niveles){
  Arbol arbol;

  LSystem lsystem;

  Rama rr;
  Rama ra;
  Rama rb;
  Rama rc;
  Rama rd;


  rr.x=0;
  rr.y=0;
  rr.z=2;


  ra.x=-1;
  ra.y=0;
  ra.z=0.5;

  rb.x=0;
  rb.y=2;
  rb.z=0.5;

  rc.x=2;
  rc.y=0;
  rc.z=0.5;

  rd.x=0;
  rd.y=-2;
  rd.z=0.5;


  ra.hijos={{-1,0,0.8,{}},{-0.5,1,0.5,{}},{-0.5,-1,0.5,{}}};

  LTreeNodo nodo{"r",{{"a",{}},{"b",{}},{"c",{}},{"d",{}},{"r",{}}}};
//  LTreeNodo nodo2{"a",{{"a",{}},{"b",{}},{"d",{}}}};
//  LTreeNodo nodo3{"b",{{"b",{}},{"a",{}},{"c",{}}}};
//  LTreeNodo nodo4{"c",{{"c",{}},{"b",{}},{"d",{}}}};
//  LTreeNodo nodo5{"d",{{"d",{}},{"a",{}},{"c",{}}}};

  lsystem.maxNivel=niveles;
  lsystem.agrLetra("r",rr);

  lsystem.agrLetra("a",ra);
  lsystem.agrLetra("b",rb);
  lsystem.agrLetra("c",rc);
  lsystem.agrLetra("d",rd);

  lsystem.agrRegla("r",nodo);
 // lsystem.agrRegla("a",nodo2);
  //lsystem.agrRegla("b",nodo3);
  //lsystem.agrRegla("c",nodo4);
  //lsystem.agrRegla("d",nodo5);

  lsystem.generar(arbol,"r");
  arbol.reduccion=0.8;
  return arbol;
}

