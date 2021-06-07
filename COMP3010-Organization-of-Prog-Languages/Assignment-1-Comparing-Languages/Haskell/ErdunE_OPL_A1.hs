module Main where

cartesian :: [[a]]  -> [[a]]
cartesian [] = []
cartesian [xs] = [[x] | x <- xs]
cartesian (as:xs) = concat [[a:ys | ys <- cartesian xs] | a <- as]

main :: IO ()
main = print $ cartesian [[1, 2, 3], [5, 0], [4, 3]]
