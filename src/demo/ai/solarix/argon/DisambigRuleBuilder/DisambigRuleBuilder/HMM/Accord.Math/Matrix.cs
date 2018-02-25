// Accord Math Library
// Accord.NET framework
// http://www.crsouza.com
//
// Copyright © César Souza, 2009-2011
// cesarsouza at gmail.com
//

namespace Accord.Math
{
    using System;
    using System.Collections.Generic;
    using System.Data;

    /// <summary>
    /// Static class Matrix. Defines a set of extension methods
    /// that operates mainly on multidimensional arrays and vectors.
    /// </summary>
    public static class Matrix
    {

        #region Matrix Construction
        /// <summary>
        ///   Creates a index vector.
        /// </summary>
        public static int[] Indexes(int from, int to)
        {
            int[] r = new int[to - from];
            for (int i = 0; i < r.Length; i++)
                r[i] = from++;
            return r;
        }
        #endregion


        #region Subsection and elements selection

        /// <summary>Returns a subvector extracted from the current vector.</summary>
        /// <param name="data">The vector to return the subvector from.</param>
        /// <param name="indexes">Array of indices.</param>
        /// <remarks>
        ///   Routine adapted from Lutz Roeder's Mapack for .NET, September 2000.
        /// </remarks>
        public static T[] Submatrix<T>(this T[] data, int[] indexes)
        {
            T[] X = new T[indexes.Length];

            for (int i = 0; i < indexes.Length; i++)
            {
                X[i] = data[indexes[i]];
            }

            return X;
        }


        /// <summary>
        ///   Stores a column vector into the given column position of the matrix.
        /// </summary>
        public static T[,] SetColumn<T>(this T[,] m, int index, T[] column)
        {
            for (int i = 0; i < column.Length; i++)
                m[i, index] = column[i];

            return m;
        }

        /// <summary>
        ///   Gets a row vector from a matrix.
        /// </summary>
        public static T[] GetRow<T>(this T[,] m, int index)
        {
            T[] row = new T[m.GetLength(1)];

            for (int i = 0; i < row.Length; i++)
                row[i] = m[index, i];

            return row;
        }

        /// <summary>
        ///   Stores a row vector into the given row position of the matrix.
        /// </summary>
        public static T[,] SetRow<T>(this T[,] m, int index, T[] row)
        {
            for (int i = 0; i < row.Length; i++)
                m[index, i] = row[i];

            return m;
        }


        /// <summary>
        ///   Gets the indices of all elements matching a certain criteria.
        /// </summary>
        /// <typeparam name="T">The type of the array.</typeparam>
        /// <param name="data">The array to search inside.</param>
        /// <param name="func">The search criteria.</param>
        public static int[] Find<T>(this T[] data, Func<T, bool> func)
        {
            return Find(data, func, false);
        }

        /// <summary>
        ///   Gets the indices of all elements matching a certain criteria.
        /// </summary>
        /// <typeparam name="T">The type of the array.</typeparam>
        /// <param name="data">The array to search inside.</param>
        /// <param name="func">The search criteria.</param>
        /// <param name="firstOnly">
        ///    Set to true to stop when the first element is
        ///    found, set to false to get all elements.
        /// </param>
        public static int[] Find<T>(this T[] data, Func<T, bool> func, bool firstOnly)
        {
            List<int> idx = new List<int>();
            for (int i = 0; i < data.Length; i++)
            {
                if (func(data[i]))
                {
                    if (firstOnly)
                        return new int[] { i };
                    else idx.Add(i);
                }
            }
            return idx.ToArray();
        }

        /// <summary>
        ///   Gets the indices of all elements matching a certain criteria.
        /// </summary>
        /// <typeparam name="T">The type of the array.</typeparam>
        /// <param name="data">The array to search inside.</param>
        /// <param name="func">The search criteria.</param>
        public static int[][] Find<T>(this T[,] data, Func<T, bool> func)
        {
            return Find(data, func, false);
        }

        /// <summary>
        ///   Gets the indices of all elements matching a certain criteria.
        /// </summary>
        /// <typeparam name="T">The type of the array.</typeparam>
        /// <param name="data">The array to search inside.</param>
        /// <param name="func">The search criteria.</param>
        /// <param name="firstOnly">
        ///    Set to true to stop when the first element is
        ///    found, set to false to get all elements.
        /// </param>
        public static int[][] Find<T>(this T[,] data, Func<T, bool> func, bool firstOnly)
        {
            List<int[]> idx = new List<int[]>();
            for (int i = 0; i < data.GetLength(0); i++)
            {
                for (int j = 0; j < data.GetLength(1); j++)
                {
                    if (func(data[i, j]))
                    {
                        if (firstOnly)
                            return new int[][] { new int[] { i, j } };
                        else idx.Add(new int[] { i, j });
                    }
                }
            }
            return idx.ToArray();
        }
        #endregion


        #region Matrix Characteristics
        /// <summary>
        ///   Gets the maximum element in a vector.
        /// </summary>
        public static T Max<T>(this T[] values, out int imax) where T : IComparable
        {
            imax = 0;
            T max = values[0];
            for (int i = 1; i < values.Length; i++)
            {
                if (values[i].CompareTo(max) > 0)
                {
                    max = values[i];
                    imax = i;
                }
            }
            return max;
        }

        /// <summary>
        ///   Gets the maximum element in a vector.
        /// </summary>
        public static T Max<T>(this T[] values) where T : IComparable
        {
            int imax;
            return Max(values, out imax);
        }

        /// <summary>
        ///   Gets the minimum element in a vector.
        /// </summary>
        public static T Min<T>(this T[] values, out int imax) where T : IComparable
        {
            imax = 0;
            T max = values[0];
            for (int i = 1; i < values.Length; i++)
            {
                if (values[i].CompareTo(max) < 0)
                {
                    max = values[i];
                    imax = i;
                }
            }
            return max;
        }

        /// <summary>
        ///   Gets the minimum element in a vector.
        /// </summary>
        public static T Min<T>(this T[] values) where T : IComparable
        {
            int imin = 0;
            return Min(values, out imin);
        }
        #endregion


        #region Conversions

        /// <summary>
        ///   Converts a jagged-array into a multidimensional array.
        /// </summary>
        public static T[,] ToMatrix<T>(this T[][] array)
        {
            int rows = array.Length;
            if (rows == 0) return new T[rows, 0];
            int cols = array[0].Length;

            T[,] m = new T[rows, cols];
            for (int i = 0; i < rows; i++)
                for (int j = 0; j < cols; j++)
                    m[i, j] = array[i][j];

            return m;
        }

        /// <summary>
        ///   Converts an array into a multidimensional array.
        /// </summary>
        public static T[,] ToMatrix<T>(this T[] array)
        {
            T[,] m = new T[1, array.Length];
            for (int i = 0; i < array.Length; i++)
                m[0, i] = array[i];

            return m;
        }

        /// <summary>
        ///   Converts a multidimensional array into a jagged-array.
        /// </summary>
        public static T[][] ToArray<T>(this T[,] matrix)
        {
            int rows = matrix.GetLength(0);

            T[][] array = new T[rows][];
            for (int i = 0; i < rows; i++)
                array[i] = matrix.GetRow(i);

            return array;
        }

        /// <summary>
        ///   Converts a DataTable to a double[,] array.
        /// </summary>
        public static double[,] ToMatrix(this DataTable table, out string[] columnNames)
        {
            double[,] m = new double[table.Rows.Count, table.Columns.Count];
            columnNames = new string[table.Columns.Count];

            for (int j = 0; j < table.Columns.Count; j++)
            {
                for (int i = 0; i < table.Rows.Count; i++)
                {
                    if (table.Columns[j].DataType == typeof(System.String))
                    {
                        m[i, j] = Double.Parse((String)table.Rows[i][j], System.Globalization.CultureInfo.InvariantCulture);
                    }
                    else if (table.Columns[j].DataType == typeof(System.Boolean))
                    {
                        m[i, j] = (Boolean)table.Rows[i][j] ? 1.0 : 0.0;
                    }
                    else
                    {
                        m[i, j] = (Double)table.Rows[i][j];
                    }
                }

                columnNames[j] = table.Columns[j].Caption;
            }
            return m;
        }

        /// <summary>
        ///   Converts a DataTable to a double[,] array.
        /// </summary>
        public static double[,] ToMatrix(this DataTable table)
        {
            String[] names;
            return ToMatrix(table, out names);
        }

        /// <summary>
        ///   Converts a DataTable to a double[][] array.
        /// </summary>
        public static double[][] ToArray(this DataTable table)
        {
            double[][] m = new double[table.Rows.Count][];

            for (int i = 0; i < table.Rows.Count; i++)
            {
                m[i] = new double[table.Columns.Count];

                for (int j = 0; j < table.Columns.Count; j++)
                {
                    if (table.Columns[j].DataType == typeof(System.String))
                    {
                        m[i][j] = Double.Parse((String)table.Rows[i][j], System.Globalization.CultureInfo.InvariantCulture);
                    }
                    else if (table.Columns[j].DataType == typeof(System.Boolean))
                    {
                        m[i][j] = (Boolean)table.Rows[i][j] ? 1.0 : 0.0;
                    }
                    else
                    {
                        m[i][j] = (Double)table.Rows[i][j];
                    }
                }
            }
            return m;
        }

        /// <summary>
        ///   Converts a DataColumn to a double[] array.
        /// </summary>
        public static double[] ToArray(this DataColumn column)
        {
            double[] m = new double[column.Table.Rows.Count];

            for (int i = 0; i < m.Length; i++)
            {
                object b = column.Table.Rows[i][column];

                if (column.DataType == typeof(System.String))
                {
                    m[i] = Double.Parse((String)b, System.Globalization.CultureInfo.InvariantCulture);
                }
                else if (column.DataType == typeof(System.Boolean))
                {
                    m[i] = (Boolean)b ? 1.0 : 0.0;
                }
                else
                {
                    m[i] = (Double)b;
                }
            }

            return m;
        }
        #endregion

    }
}
