#include <iostream>
#include <stddef.h>
#include <memory>
class Matrix
{
protected:
    int rows_num, columns_num;
    std::shared_ptr<float[]> data;

public:
    Matrix()
    {
        data = nullptr;
        rows_num = 0;
        columns_num = 0;
    }
    ~Matrix()
    {
        clear();
    }
    Matrix(int r, int c)
    {

        data = std::shared_ptr<float[]>(new float[r * c]);
        rows_num = r;
        columns_num = c;
    }

    Matrix(const Matrix &mat)
    {
        rows_num = mat.rows_num;
        columns_num = mat.columns_num;
        if (mat.rows_num == 0 || mat.columns_num == 0)
        {
            data.reset();
        }
        data = std::shared_ptr<float[]>(new float[rows_num * columns_num]);
        for (int i = 0; i < mat.rows_num; i++)
        {
            for (int j = 0; j < mat.columns_num; j++)
            {
                (*this)(i, j) = mat(i, j);
            }
        }
    }
    Matrix &operator=(const Matrix &mat)
    {
        rows_num = mat.rows_num;
        columns_num = mat.columns_num;
        if (mat.rows_num == 0 || mat.columns_num == 0)
        {
            data = nullptr;
        }
        for (int i = 0; i < mat.rows_num; i++)
        {
            for (int j = 0; j < mat.columns_num; j++)
            {
                (*this)(i, j) = mat(i, j);
            }
        }
        return *this;
    }

    Matrix(Matrix &&mat)
    {
        rows_num = mat.rows_num;
        columns_num = mat.columns_num;
        data = mat.data;
        mat.clear();
    }
    Matrix &operator=(Matrix &&mat)
    {
        rows_num = mat.rows_num;
        columns_num = mat.columns_num;
        data = mat.data;
        mat.clear();
        return *this;
    }

    void transpose()
    {
        Matrix tmp(columns_num, rows_num);
        for (int i = 0; i < rows_num; i++)
        {
            for (int j = 0; j < columns_num; j++)
            {
                tmp(j, i) = (*this)(i, j);
            }
        }
        (*this) = tmp;
    }

    void clear()
    {
        data.reset();
        rows_num = 0;
        columns_num = 0;
    }
    int getRowsNum() const noexcept { return rows_num; };
    int getColumnsNum() const noexcept { return columns_num; };
    float &operator()(int r, int c)
    {
        return data.get()[r * columns_num + c];
    }

    float operator()(int r, int c) const
    {
        return data.get()[r * columns_num + c];
    }
    friend std::ostream &operator<<(std::ostream &os, const Matrix &mat)
    {
        for (int i = 0; i < mat.rows_num; i++)
        {
            for (int j = 0; j < mat.columns_num; j++)
            {
                os << mat(i, j) << " ";
            }
            os << "\n";
        }
        return os;
    }

    static Matrix mult_matrix(Matrix matrix_1, Matrix matrix_2)
    {
        if (matrix_1.getColumnsNum() != matrix_2.getRowsNum())
            return Matrix();

        Matrix result(matrix_1.getRowsNum(), matrix_2.getColumnsNum());
        matrix_2.transpose();

        for (int i = 0; i < matrix_1.getRowsNum(); ++i)
        {
            for (int j = 0; j < matrix_2.getRowsNum(); ++j)
            {
                result(i, j) = 0;
                float res = 0;
                float zero = 0;

                int len = matrix_2.getColumnsNum();

                float *data_1 = &matrix_1.data.get()[matrix_1.columns_num * i];
                float *data_2 = &matrix_2.data.get()[matrix_2.columns_num * j];
                __asm__("movss xmm2, %[zero_p]\n"
                    "mov rax, %[data1]\n"
                    "mov rbx, %[data2]\n"
                    "mov rcx, 0\n"
                    "add_loop:\n"
                    "cmp ecx, %[len_p]\n"
                    "jge add_loop_end\n"
                    "add rcx, 4\n"
                    "cmp ecx, %[len_p]\n"
                    "jle united_add\n"
                    "jmp splitted_add\n"
                    "united_add:\n"
                    "movups xmm0, xmmword ptr [rax]\n"
                    "movups xmm1, xmmword ptr [rbx]\n"
                    "mulps xmm0, xmm1\n"
                    "addps xmm0, xmm0 \n"
                    "addps xmm0, xmm0 \n"
                    "addss xmm2, xmm0\n"
                    "add rax, 16\n"
                    "add rbx, 16\n"
                    "jmp add_loop\n"
                    "splitted_add:\n"
                    "sub rcx, 4\n"
                    "mov edx, %[len_p]\n"
                    "sub rdx, rcx\n"
                    "mov rcx, rdx\n"
                    "splitted_add_loop:\n"
                    "movss xmm0, dword ptr [rax]\n"
                    "movss xmm1, dword ptr [rbx]\n"
                    "mulss xmm0, xmm1\n"
                    "addss xmm2, xmm0\n"
                    "add rax, 4\n"
                    "add rbx, 4\n"
                    "loop splitted_add_loop\n"
                    "add_loop_end:\n"
                    "movss %[res_p], xmm2\n"
                    : [res_p] "=m"(res)
                    :
                    [data1] "m"(data_1),
                    [data2] "m"(data_2),
                    [len_p] "m"(len),
                    [zero_p] "m"(zero)
                    :);
                result(i, j) += res;
            }
        }
        return result;
    }
};

int main(int argc, char const *argv[])
{
    srand(time(nullptr));
    std::cout << __builtin_cpu_supports("sse") << "\n";
    std::cout << __builtin_cpu_supports("sse2") << "\n";
    std::cout << __builtin_cpu_supports("sse3") << "\n";
    std::cout << __builtin_cpu_supports("avx") << "\n";
    std::cout << __builtin_cpu_supports("avx2") << "\n";
    std::cout << __builtin_cpu_supports("avx512f") << "\n";

    std::size_t rows_num, columns_num;
    std::cout << "Кол-во строк: ";
    std::cin >> rows_num;
    std::cout << "Кол-во столбцов: ";
    std::cin >> columns_num;
    Matrix matrix_1(rows_num, columns_num);
    for (int i = 0; i < matrix_1.getRowsNum(); i++)
    {
        for (int j = 0; j < matrix_1.getColumnsNum(); j++)
        {
            matrix_1(i, j) = rand() % 10;
        }
    }

    std::cout << "Кол-во строк: ";
    std::cin >> rows_num;
    std::cout << "Кол-во столбцов: ";
    std::cin >> columns_num;
    Matrix matrix_2(rows_num, columns_num);
    for (int i = 0; i < matrix_2.getRowsNum(); i++)
    {
        for (int j = 0; j < matrix_2.getColumnsNum(); j++)
        {
            matrix_2(i, j) = rand() % 10;
        }
    }

    std::cout << "Mat1\n"
              << matrix_1 << "\n";
    std::cout << "Mat2\n"
              << matrix_2 << "\n";

    auto res = Matrix::mult_matrix(matrix_1, matrix_2);
    std::cout << "Result\n" << res;

    return 0;
}
