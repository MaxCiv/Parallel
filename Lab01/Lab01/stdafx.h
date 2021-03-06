// stdafx.h: включаемый файл для стандартных системных включаемых файлов
// или включаемых файлов для конкретного проекта, которые часто используются, но
// не часто изменяются
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>



// TODO: Установите здесь ссылки на дополнительные заголовки, требующиеся для программы
// MC# Examples
// Parallel matrix multiplication.
//
//using System;
//public class MatrixMultiplierParallel
//{
//	public static void Main()
//	{
//		int         i, j;
//
//		int N = 1000;
//		int M = 6;
//		double[, ]   A = new double[N, N];
//		double[, ]   B = new double[N, N];
//		double[, ]   C = new double[N, N];
//
//		Random      rnd = new Random();
//
//		//  Matrix content generation
//
//		for (i = 0; i < N; ++i)
//		{
//			for (j = 0; j < N; ++j)
//			{
//				A[i, j] = rnd.NextDouble();
//				B[i, j] = rnd.NextDouble();
//				C[i, j] = 0.0;
//			}
//		}
//
//		// Divide matrix between asynchronous processes
//
//		int q = N / M,
//			r = N % M;
//
//		int from = 0, to;
//
//		MatrixMultiplierParallel mmp = new MatrixMultiplierParallel();
//
//		DateTime dt1 = DateTime.Now; // Check time
//
//		for (i = 0; i < M; ++i)
//		{
//			to = from + q + (i < r ? 1 : 0);
//
//			mmp.Multiply(N, A, B, C, from, to, mmp.sendStop); // Start the async method
//			from = to;
//		}
//
//		for (i = 0; i < M; ++i) mmp.getStop ? (); // Wait the process termination
//
//		Console.WriteLine("Matrix size: {0}, Number of parts: {1}.", N, M);
//		Console.WriteLine("Time was " + (DateTime.Now - dt1).TotalSeconds + " sec."); // Check the time
//		Console.ReadLine();
//	}
//
//	public handler getStop int() & channel sendStop(int x)
//	{
//		return x;
//	}
//
//	public async Multiply(int N, double[, ] A, double[, ] B, double[, ] C, int from, int to, 
//		channel(int) sendStop) // Async!
//	{
//		for (int i = from; i < to; i++)
//		{
//			for (int j = 0; j < N; j++)
//			{
//				for (int k = 0; k < N; k++) C[i, j] += A[i, k] * B[k, j];
//			}
//		}
//		sendStop !(0);
//	}
//}