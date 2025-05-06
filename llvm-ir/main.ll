target triple = "x86_64-pc-linux-gnu"

@.str = private unnamed_addr constant [5 x i8] c"%zu\0A\00", align 1
@str = private unnamed_addr constant [14 x i8] c"Hello, World!\00", align 1

; Function Attrs: nofree nounwind uwtable
define dso_local i32 @main() local_unnamed_addr #0 {
  %1 = tail call i32 (i8*, ...) @printf(i8* getelementptr ([5 x i8], [5 x i8]* @.str, i64 0, i64 0), i64 noundef 0)
  %2 = tail call i32 (i8*, ...) @printf(i8* getelementptr ([5 x i8], [5 x i8]* @.str, i64 0, i64 0), i64 noundef 1)
  %3 = tail call i32 (i8*, ...) @printf(i8* getelementptr ([5 x i8], [5 x i8]* @.str, i64 0, i64 0), i64 noundef 2)
  %4 = tail call i32 (i8*, ...) @printf(i8* getelementptr ([5 x i8], [5 x i8]* @.str, i64 0, i64 0), i64 noundef 3)
  %5 = tail call i32 (i8*, ...) @printf(i8* getelementptr ([5 x i8], [5 x i8]* @.str, i64 0, i64 0), i64 noundef 4)
  %6 = tail call i32 (i8*, ...) @printf(i8* getelementptr ([5 x i8], [5 x i8]* @.str, i64 0, i64 0), i64 noundef 5)
  %7 = tail call i32 (i8*, ...) @printf(i8* getelementptr ([5 x i8], [5 x i8]* @.str, i64 0, i64 0), i64 noundef 6)
  %8 = tail call i32 (i8*, ...) @printf(i8* getelementptr ([5 x i8], [5 x i8]* @.str, i64 0, i64 0), i64 noundef 7)
  %9 = tail call i32 (i8*, ...) @printf(i8* getelementptr ([5 x i8], [5 x i8]* @.str, i64 0, i64 0), i64 noundef 8)
  %10 = tail call i32 (i8*, ...) @printf(i8* getelementptr ([5 x i8], [5 x i8]* @.str, i64 0, i64 0), i64 noundef 9)
  %11 = tail call i32 @puts(i8* getelementptr ([14 x i8], [14 x i8]* @str, i64 0, i64 0))
  ret i32 0
}

; Function Attrs: nofree nounwind
declare i32 @printf(i8*, ...) local_unnamed_addr #1

; Function Attrs: nofree nounwind
declare i32 @puts(i8* ) local_unnamed_addr #2
