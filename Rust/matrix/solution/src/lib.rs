
use std::ops::{Add, Mul};

#[derive(Debug)]
pub struct Matrix<T: Clone> {   
    cells: [[T; 2];2],
}

#[derive(Debug, Clone, PartialEq)]
pub struct Cell<T>(pub T);

impl Add<Cell<String>> for Cell<i32> {
    type Output = Cell<String>; 

    fn add(self, other: Cell<String>) -> Self::Output {
        if self.0 >= 0 {
            let mut num_str = self.0.to_string();
            num_str.push(' ');
            num_str.push_str(&other.0);
            Cell(num_str)
        } else {
            let mut num_str = self.0.abs().to_string();
            let mut rev_str = other.0.chars().rev().collect::<String>();

            rev_str.push(' ');
            rev_str.push_str(&num_str);
            Cell(rev_str)
        }
    }
}


impl Mul<Cell<String>> for Cell<i32> {
    type Output = Cell<String>; 

    fn mul(self, other: Cell<String>) -> Self::Output {
        if self.0 >= 0 {
            let num = self.0;
            let mut result = String::new();

            for _ in 0..num {
                result.push_str(&other.0);
            }

            Cell(result)
        } else {
            let num = self.0.abs();
            let mut rev_str = other.0.chars().rev().collect::<String>();

            let mut result = String::new();

            for _ in 0..num {
                result.push_str(&rev_str);
            }

            Cell(result)
        }
    }
}


impl<T: Clone> Matrix<T> {
    /// Данните се очаква да бъдат подадени със статичен масив -- вижте по-долу за примери за
    /// конструиране. Какви може да са елементите? Ще тестваме само с два типа: String и i32.
    ///
    /// Очаква се да бъдат подадени по редове, от ляво надясно. Тоест, ако подадем като вход списък
    /// с елементи: 1, 2, 3, 4, се очаква конструираната матрица:
    ///
    /// | 1 2 |
    /// | 3 4 |
    ///
    /// Забележете, че подаваме като вход някакъв slice -- reference тип. Не очакваме матрицата да
    /// държи reference, клонирайте си данните, за да имате ownership.
    ///
    pub fn new(data: &[T; 4]) -> Matrix<T> {
        Matrix {
            cells: [
                [data[0].clone(), data[1].clone()],
                [data[2].clone(), data[3].clone()]
            ]
        }
    }

    /// Връща вектор, който съдържа в себе си всички 4 елемента на матрицата, наредени по редове,
    /// от ляво надясно и от горе надолу, обвити в `Cell`. Тоест, ако матрицата изглежда така:
    ///
    /// | 1 2 |
    /// | 3 4 |
    ///
    /// Очакваме `.by_row` да върне елементите в ред: 1, 2, 3, 4
    ///
    pub fn by_row(&self) -> Vec<Cell<T>> {
        let mut vec = Vec::new();

        for row in 0..2 {
            for column in 0..2 {
                vec.push(Cell(self.cells[row][column].clone())); 
            }
        }

        vec
    }

    /// Връща вектор, който съдържа в себе си всички 4 елемента на матрицата, наредени по колони,
    /// от горе надолу и от ляво надясно, Обвити в `Cell`. Тоест, ако матрицата изглежда така:
    ///
    /// | 1 2 |
    /// | 3 4 |
    ///
    /// Очакваме `.by_col` да върне елементите в ред: 1, 3, 2, 4
    ///
    pub fn by_col(&self) -> Vec<Cell<T>> {
        let mut vec = Vec::new();

        for column in 0..2 {
            for row in 0..2 {
                vec.push(Cell(self.cells[row][column].clone())); 
            }
        }

        vec

    }
}


impl Add<Matrix<String>> for Matrix<i32> {
    type Output = Matrix<String>;

    fn add(self, other: Matrix<String>) -> Self::Output {
        let left_values = self.by_row();
        let right_values = other.by_row();

        let mut result = Vec::new();

        for i in 0..4 {
            let temp = left_values[i].clone() + right_values[i].clone();
            result.push(temp.0);
        }

        Matrix::new(result.as_slice().try_into().unwrap())
    }

}

impl Mul<Matrix<String>> for Matrix<i32> {
    type Output = String;

    fn mul(self, other: Matrix<String>) -> Self::Output {
        let mut result = String::new();

        let rows = self.by_row();
        let columns = other.by_col();

        for i in 0..4 {
            result.push_str(&((rows[i].clone() * columns[i].clone()).0));
            result.push(' ');
        }

        result.truncate(result.len() - 1);
        result
    }
}



#[cfg(test)]
mod tests{
    use crate::Cell;
    use crate::Matrix;

    #[test]
    fn test_matrix_new() {
        let matrix = super::Matrix::new(&[1,2,3,4]);
        assert_eq!(matrix.cells[0][0], 1);
    }

    #[test]
    fn test_matrix_by_row() {
        let matrix = super::Matrix::new(&[1,2,3,4]);
        let by_row = matrix.by_row();

        assert_eq!(super::Cell(1), by_row[0]);
        assert_eq!(super::Cell(2), by_row[1]);
    }

    #[test]
    fn test_matrix_by_column() {
        let matrix = super::Matrix::new(&[1,2,3,4]);
        let by_col = matrix.by_col();

        assert_eq!(super::Cell(1), by_col[0]);
        assert_eq!(super::Cell(3), by_col[1]);
    }

    #[test]
    fn test_add_cells_positive() {
        assert_eq!(Cell(22) + Cell(String::from("years ago")), Cell(String::from("22 years ago")));
        assert_eq!(Cell(0) + Cell(String::from("expectation")), Cell(String::from("0 expectation")));
    }

    #[test]
    fn test_add_cells_negative() {
        assert_eq!(Cell(-4) + Cell(String::from("xirtam")), Cell(String::from("matrix 4")))
    }

    #[test]
    fn test_mul_cells_positive() {
        assert_eq!(Cell(3) * Cell(String::from("woah!")), Cell(String::from("woah!woah!woah!")));
        assert_eq!(Cell(0) * Cell(String::from("woah?")), Cell(String::from("")));
    }

    #[test]
    fn test_mul_cells_negative() {
        assert_eq!(Cell(-3) * Cell(String::from(",regdab")), Cell(String::from("badger,badger,badger,")));
    }

    #[test]
    fn test_add_matrices() {
        let data1 = [1,2,3,4];
        let data2 = [String::from("one"), String::from("two"), String::from("three"), String::from("four")];
        let result = vec![
            Cell(String::from("1 one")), 
            Cell(String::from("2 two")),
            Cell(String::from("3 three")),
            Cell(String::from("4 four"))];

        let m1 = Matrix::new(&data1);
        let m2 = Matrix::new(&data2);

        let m3 = m1 + m2;

        assert_eq!(m3.by_row(), result);
    }

    #[test]
    fn test_mul_matrices() {
        let data1 = [1, 2, 3, 1];
        let data2 = [String::from("one"), String::from("two"), String::from("three"), String::from("you get it")];
        let expected_result = String::from("one threethree twotwotwo you get it");

        let m1 = Matrix::new(&data1);
        let m2 = Matrix::new(&data2);

        let result = m1 * m2;

        assert_eq!(expected_result, result);
    }

    // За помощни цели:
    fn string_cell_vec(s1: &str, s2: &str, s3: &str, s4: &str) -> Vec<Cell<String>> {
        [s1, s2, s3, s4].into_iter().map(String::from).map(Cell).collect::<Vec<Cell<String>>>()
    }

    #[test]
    fn test_basic() {
        assert_eq!((Cell(4) + Cell(String::from("badger"))).0, String::from("4 badger"));
        assert_eq!((Cell(2) * Cell(String::from("mushroom"))).0, String::from("mushroommushroom"));

        let matrix1 = Matrix::new(&[1, 2, 3, 4]);
        let matrix2 = Matrix::new(&[
            String::from("one"), String::from("two"),
            String::from("three"), String::from("four")
        ]);
        assert_eq!(matrix1.by_row()[0], Cell(1));
        assert_eq!(matrix1.by_col()[0], Cell(1));

        assert_eq!(
            (matrix1 + matrix2).by_row(),
            string_cell_vec("1 one", "2 two", "3 three", "4 four")
        );

        let matrix1 = Matrix::new(&[1, 1, 1, 1]);
        let matrix2 = Matrix::new(&[
            String::from("one"), String::from("two"),
            String::from("three"), String::from("four")
        ]);
        assert_eq!(matrix1 * matrix2, String::from("one three two four"));
    }

   

}

