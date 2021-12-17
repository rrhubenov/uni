

#[derive(Default, Clone)]
pub struct SomeStruct {
    data: Vec<u32>
}

pub struct StaticStack<T> {
    size: usize,
    data: [T; 256],
    sp: u8,
}

impl<T> StaticStack<T> where T: Default {
    pub fn new() -> StaticStack<T> {
        StaticStack {
            sp: 0,
            size: 256,
            data: [T::default(); 256]
        }
    }

    pub fn size(&self) -> usize {
        self.size
    }

    pub fn is_empty(&self) -> bool {
        self.sp == 0
    }

    pub fn is_full(&self) -> bool {
        usize::from(self.sp) == self.size - 1
    }

    pub fn push(&mut self, element: T) {
        self.data[usize::from(self.sp)] = element;
        self.sp += 1;
    }

    pub fn pop(&mut self) {
        self.sp -= 1;
    }
}