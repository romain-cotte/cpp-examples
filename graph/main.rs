use std::cmp::Ordering;
use std::collections::BinaryHeap;
use std::collections::HashMap;
use std::collections::LinkedList;
use std::usize;
use std::vec::Vec;

#[derive(Debug)]
pub enum DirectedType {
    Directed,
    Undirected,
}

pub struct Graph <T> {
    vertices: HashMap<usize, T>,
    edges: HashMap<usize, Vec<(usize, usize)>>,
    is_directed: DirectedType,
}


#[derive(Debug, Copy, Clone, Eq, PartialEq)]
struct State {
    cost: usize,
    position: usize,
}

impl Ord for State {
    fn cmp(&self, s: &State) -> Ordering {
        s.cost.cmp(&self.cost)
    }
}

impl PartialOrd for State {
    fn partial_cmp(&self, s: &State) -> Option<Ordering> {
        Some(self.cmp(s))
    }
}


impl<T> Graph<T> {
    pub fn new(is_directed: DirectedType) -> Graph <T> {
        Graph {
            vertices: HashMap::new(),
            edges: HashMap::new(),
            is_directed: is_directed
        }
    }

    pub fn add_vertice(&mut self, n: usize, content: T) {
        if self.vertices.contains_key(&n) {
            panic!("already here");
        } else {
            self.vertices.insert(n, content);
        }
    }

    pub fn len(&self) -> usize {
        self.vertices.len()
    }

    pub fn add_edge(&mut self, start: usize, end: usize, weight: usize) {
        if !self.vertices.contains_key(&start) || !self.vertices.contains_key(&end) {
            panic!("graph doesn't have these vertices!");
        } else {
            self.edges.entry(start)
                .or_insert(vec![])
                .push((end, weight));
        }
    }

    // Deep first search
    pub fn dfs(&self, start: usize) {
        match self.edges.get(&start) {
            Some(v) => {
                for &(i, _) in v.iter() {
                    println!("{:?}->{:?}", start, i);
                    self.dfs(i);
                }
            },
            None => ()
        }
    }

    // Breadth first search
    pub fn bfs(&self, start: usize) -> Vec<(usize, usize)> {
        let mut v: Vec<(usize, usize)> = vec![];
        let mut l: LinkedList<usize> = LinkedList::new();
        l.push_back(start);
        while let Some(ref k) = l.pop_front() {
            match self.edges.get(k) {
                Some(vertices) => {
                    for &(i, _) in vertices.iter() {
                        v.push((*k, i));
                        l.push_back(i);
                    }
                }
                None => ()
            }
        }
        v
    }

    pub fn dijkstra(&self, start: usize, goal: usize) -> Option<usize> {
        if !self.vertices.contains_key(&start) ||
           !self.vertices.contains_key(&goal) {
            println!("start or goal not present");
            return None
        }
        let mut max = 0;
        for (i, _) in self.vertices.iter() {
            if i > &max {
                max = *i;
            }
        }
        let mut dist = vec![usize::MAX; max + 1];
        dist[start] = 0;
        let mut heap = BinaryHeap::new();
        heap.push(State { cost: 0, position: start });

        while let Some(ref state) = heap.pop() {
            if state.position == goal {
                return Some(state.cost)
            }
            if dist[state.position] < state.cost { continue }
            if let Some(ref vertices) = self.edges.get(&state.position) {
                for &(i, w) in vertices.iter() {
                    if dist[i] > dist[state.position] + w {
                        dist[i] = dist[state.position] + w;
                        heap.push(State {
                            cost: dist[state.position] + w,
                            position: i
                        })
                    }
                }
            }
        }
        None
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn bfs_test() {
        let mut g: Graph<usize> = Graph::new(DirectedType::Directed);
        g.add_vertice(1, 1);
        g.add_vertice(2, 2);
        g.add_vertice(3, 3);
        g.add_vertice(4, 4);
        g.add_vertice(5, 5);
        g.add_vertice(6, 6);
        g.add_edge(1, 2, 1);
        g.add_edge(2, 6, 1);
        g.add_edge(1, 3, 1);
        g.add_edge(3, 4, 1);
        g.add_edge(4, 5, 1);
        assert_eq!(g.len(), 6);
        let v = g.bfs(1);
        assert_eq!(v, [(1, 2), (1, 3), (2, 6), (3, 4), (4, 5)]);
        let w: Vec<i32> = vec![0, 1, 2];
        let t: Option<&i32> = w.get(0);

    }

    #[test]
    fn dijkstra_test() {
        // See example on https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-using-priority_queue-stl/
        let mut g: Graph<usize> = Graph::new(DirectedType::Undirected);
        g.add_vertice(0, 0);
        g.add_vertice(1, 1);
        g.add_vertice(2, 2);
        g.add_vertice(3, 3);
        g.add_vertice(4, 4);
        g.add_vertice(5, 5);
        g.add_vertice(6, 6);
        g.add_vertice(7, 7);
        g.add_vertice(8, 8);
        g.add_edge(0, 1, 4);
        g.add_edge(0, 7, 8);
        g.add_edge(1, 2, 8);
        g.add_edge(1, 7, 11);
        g.add_edge(2, 3, 7);
        g.add_edge(2, 5, 4);
        g.add_edge(2, 8, 2);
        g.add_edge(3, 4, 9);
        g.add_edge(3, 5, 14);
        g.add_edge(5, 4, 10);
        g.add_edge(6, 5, 2);
        g.add_edge(7, 6, 1);
        g.add_edge(7, 8, 7);
        g.add_edge(8, 6, 6);
        let cost = g.dijkstra(0, 4);
        println!("cost: {:?}", cost);
    }

}
