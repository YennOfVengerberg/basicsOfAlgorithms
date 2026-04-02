class B(A):
    def f(self) -> str:
            return "B"
b = B()
b.f()

class B(A):
    def f(self, x: int) -> str:
            return f"B({x})"
b = B()
b.f(10)
b.f()

class B(A):
      def f(self) -> str:
            return super().f() + "+B"
b = B()
b.f()

class A: 
    def f(self) -> str:
        return "A"
class B:
      def g(self) -> str:
            return "B"

class C(A,B):
      ...
class C(A, B):
      pass
c = C()
c.f()
c.g()

C.mro()
c.func()

class A: 
    def f(self) -> str:
        return "A"
class B(A):
      def f(self) -> str:
            return "B" + super().f()
class C(A):
      def f(self) ->str:
            return "C -> " + super().f()
      
class D(B, C):
    pass

d = D()
d.f()
D.mro()

from abc import ABC, abstractmethod

class GraphInterface(ABC):
    @abstractmethod
    def neighbours(self, u: int) -> list[int]:
        raise NotImplementedError
    @abstractmethod
    def iter_edges(self, u:int) -> list[tuple[int, int]]:
         raise NotImplementedError

g = GraphInterface()

class ConcreteGraphInterface(GraphInterface):
     def neighbours(self, u) -> list[int]:
          pass
     def iter_edges(self, u) -> list[tuple[int, int]]:
          pass
g = ConcreteGraphInterface()     
