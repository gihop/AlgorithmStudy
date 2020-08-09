//https://programmers.co.kr/learn/courses/30/lessons/43165/solution_groups?language=kotlin
//코드는 깔끔한데 익숙치 않아서 이 코드를 해석하는데 애를 먹음.
//처음 fold 함수의 초깃값으로 리스트 {0}, i=1 시작.
//numbers에 {1, 1, 1, 1}이 있다면,
//map{it + i}는 {1}, map{it - i}는 {-1}.
//map{it + i} + map{it - i}는 {1, -1}.
//list{0,1} 일 때 map{it + 1} 은 {1,2}
//다시 fold 함수에서 list는 {1, -1}, i=1 시작.
//map{it + i} + map{it - 1}은 {2, 0, 0, -1}.
//즉 list엔 numbers에 원소들을 더하고 빼서 만들 수 있는 모든 경우의 수가 담기게 된다.
fun solution(numbers: IntArray, target: Int): Int {
    return numbers.fold(listOf(0)) { list, i ->
        list.run {
            map { it + i } + map { it - i }
        }
    }.count { it == target }
}