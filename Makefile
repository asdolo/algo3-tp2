CXX           = g++
COMPILE_FLAGS = -std=c++11 -Wall -Wextra -g
CXXFLAGS      = $(COMPILE_FLAGS)
LIBS          = 
DEL_FILE      = rm -f

#OBJECTS_CLUSTERIZACION_PRIM						= 	clusterizacion-prim.o
#OBJECTS_CLUSTERIZACION_KRUSKAL					= 	clusterizacion-kruskal.o
#OBJECTS_CLUSTERIZACION_KRUSKAL_PATH_COMPRESSION	= 	clusterizacion-kruskal-path-compression.o
OBJECTS_ARBITRAJE_BELLMAN_FORD					= 	arbitraje-bellman-ford.o
OBJECTS_ARBITRAJE_FLOYD							= 	arbitraje-floyd.o

#TARGET_CLUSTERIZACION_PRIM						= 	clusterizacion-prim
#TARGET_CLUSTERIZACION_KRUSKAL					= 	clusterizacion-kruskal
#TARGET_CLUSTERIZACION_KRUSKAL_PATH_COMPRESSION	= 	clusterizacion-kruskal-path-compression
TARGET_ARBITRAJE_BELLMAN_FORD					= 	arbitraje-bellman-ford
TARGET_ARBITRAJE_FLOYD							= 	arbitraje-floyd

all: $(TARGET_CLUSTERIZACION_PRIM) $(TARGET_CLUSTERIZACION_KRUSKAL) $(TARGET_CLUSTERIZACION_KRUSKAL_PATH_COMPRESSION) $(TARGET_ARBITRAJE_BELLMAN_FORD) $(TARGET_ARBITRAJE_FLOYD)

$(TARGET_CLUSTERIZACION_PRIM):  $(OBJECTS_CLUSTERIZACION_PRIM)  
	$(CXX) -o $(TARGET_CLUSTERIZACION_PRIM) $(OBJECTS_CLUSTERIZACION_PRIM) $(OBJCOMP) $(LIBS)

$(TARGET_CLUSTERIZACION_KRUSKAL):  $(OBJECTS_CLUSTERIZACION_KRUSKAL)  
	$(CXX) -o $(TARGET_CLUSTERIZACION_KRUSKAL) $(OBJECTS_CLUSTERIZACION_KRUSKAL) $(OBJCOMP) $(LIBS)

$(TARGET_CLUSTERIZACION_KRUSKAL_PATH_COMPRESSION):  $(OBJECTS_CLUSTERIZACION_KRUSKAL_PATH_COMPRESSION)  
	$(CXX) -o $(TARGET_CLUSTERIZACION_KRUSKAL_PATH_COMPRESSION) $(OBJECTS_CLUSTERIZACION_KRUSKAL_PATH_COMPRESSION) $(OBJCOMP) $(LIBS)


$(TARGET_ARBITRAJE_BELLMAN_FORD):  $(OBJECTS_ARBITRAJE_BELLMAN_FORD)  
	$(CXX) -o $(TARGET_ARBITRAJE_BELLMAN_FORD) $(OBJECTS_ARBITRAJE_BELLMAN_FORD) $(OBJCOMP) $(LIBS)

$(TARGET_ARBITRAJE_FLOYD):  $(OBJECTS_ARBITRAJE_FLOYD)  
	$(CXX) -o $(TARGET_ARBITRAJE_FLOYD) $(OBJECTS_ARBITRAJE_FLOYD) $(OBJCOMP) $(LIBS)

clean: 
	-$(DEL_FILE) $(OBJECTS_CLUSTERIZACION_PRIM)
	-$(DEL_FILE) $(OBJECTS_CLUSTERIZACION_KRUSKAL)
	-$(DEL_FILE) $(OBJECTS_CLUSTERIZACION_KRUSKAL_PATH_COMPRESSION)
	-$(DEL_FILE) $(OBJECTS_ARBITRAJE_BELLMAN_FORD)
	-$(DEL_FILE) $(OBJECTS_ARBITRAJE_FLOYD)
	-$(DEL_FILE) *~ core *.core
	-$(DEL_FILE) $(TARGET_CLUSTERIZACION_PRIM)
	-$(DEL_FILE) $(TARGET_CLUSTERIZACION_KRUSKAL)
	-$(DEL_FILE) $(TARGET_CLUSTERIZACION_KRUSKAL_PATH_COMPRESSION)
	-$(DEL_FILE) $(TARGET_ARBITRAJE_BELLMAN_FORD)
	-$(DEL_FILE) $(TARGET_ARBITRAJE_FLOYD)


$(TARGET_CLUSTERIZACION_PRIM).o: src/arbitraje/$(TARGET_CLUSTERIZACION_PRIM).cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(TARGET_CLUSTERIZACION_PRIM).o src/arbitraje/$(TARGET_CLUSTERIZACION_PRIM).cpp

$(TARGET_CLUSTERIZACION_KRUSKAL).o: src/arbitraje/$(TARGET_CLUSTERIZACION_KRUSKAL).cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(TARGET_CLUSTERIZACION_KRUSKAL).o src/arbitraje/$(TARGET_CLUSTERIZACION_KRUSKAL).cpp

$(TARGET_CLUSTERIZACION_KRUSKAL_PATH_COMPRESSION).o: src/arbitraje/$(TARGET_CLUSTERIZACION_KRUSKAL_PATH_COMPRESSION).cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(TARGET_CLUSTERIZACION_KRUSKAL_PATH_COMPRESSION).o src/arbitraje/$(TARGET_CLUSTERIZACION_KRUSKAL_PATH_COMPRESSION).cpp


$(TARGET_ARBITRAJE_BELLMAN_FORD).o: src/arbitraje/$(TARGET_ARBITRAJE_BELLMAN_FORD).cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(TARGET_ARBITRAJE_BELLMAN_FORD).o src/arbitraje/$(TARGET_ARBITRAJE_BELLMAN_FORD).cpp

$(TARGET_ARBITRAJE_FLOYD).o: src/arbitraje/$(TARGET_ARBITRAJE_FLOYD).cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(TARGET_ARBITRAJE_FLOYD).o src/arbitraje/$(TARGET_ARBITRAJE_FLOYD).cpp