//https://programmers.co.kr/learn/courses/30/lessons/43165/solution_groups?language=kotlin
//추후에 설명을 따로 달 것.
//코드는 깔끔한데 익숙치 않아서 이 코드를 해석하는데 애를 먹음.

fun solution(numbers: IntArray, target: Int): Int {
    return numbers.fold(listOf(0)) { list, i ->
        list.run {
            map { it + i } + map { it - i }
        }
    }.count { it == target }
}