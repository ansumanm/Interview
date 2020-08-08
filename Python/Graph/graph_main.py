from graph import Graph

if __name__ == "__main__":

    g = { "a" : ["d"],
          "b" : ["c"],
          "c" : ["b", "c", "d", "e"],
          "d" : ["a", "c"],
          "e" : ["c"],
          "f" : []
        }

    g2 = { "a" : ["d", "f"],
      "b" : ["c"],
      "c" : ["b", "c", "d", "e"],
      "d" : ["a", "c"],
      "e" : ["c"],
      "f" : ["d"]
    }

    graph = Graph(g2)

    print("Vertices of graph:")
    print(graph.vertices())

    print("Edges of graph:")
    print(graph.edges())

    print("Add vertex:")
    graph.add_vertex("z")

    print("Vertices of graph:")
    print(graph.vertices())
 
    print("Add an edge:")
    graph.add_edge({"a","z"})
    
    print("Vertices of graph:")
    print(graph.vertices())

    print("Edges of graph:")
    print(graph.edges())

    print('Adding an edge {"x","y"} with new vertices:')
    graph.add_edge({"x","y"})
    print("Vertices of graph:")
    print(graph.vertices())
    print("Edges of graph:")
    print(graph.edges())

    print('The path from vertex "a" to vertex "b":')
    path = graph.find_path("a", "b")
    print(path)

    print('The path from vertex "a" to vertex "f":')
    path = graph.find_path("a", "f")
    print(path)

    print('The path from vertex "c" to vertex "c":')
    path = graph.find_path("c", "c")
    print(path)

    print('All paths from vertex "a" to vertex "b":')
    path = graph.find_all_paths("a", "b")
    print(path)

    print('All paths from vertex "a" to vertex "f":')
    path = graph.find_all_paths("a", "f")
    print(path)

    print('All paths from vertex "c" to vertex "c":')
    path = graph.find_all_paths("c", "c")
    print(path)


    g3 = { "a" : ["d","f"],
           "b" : ["c","b"],
           "c" : ["b", "c", "d", "e"],
           "d" : ["a", "c"],
           "e" : ["c"],
           "f" : ["a"]
    }


    graph = Graph(g)
    print(graph)
    print(graph.is_connected())

    graph = Graph(g2)
    print(graph)
    print(graph.is_connected())

    graph = Graph(g3)
    print(graph)
    print(graph.is_connected())
