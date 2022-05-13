
(*Counts the occurences of char (letter) c in a char list*)
fun char_count ([], n:int) = 0.0
    | char_count (head::tail, n:int) =
        let
            val c = (Char.chr (n + (Char.ord #"A")))
            val count =
                if (Char.isAlpha head) then
                    if (Char.compare (Char.toUpper head,c) = EQUAL) then
                        1.0 + char_count(tail,n)
                    else
                        char_count(tail,n)
                else
                    char_count (tail, n)
        in
            count
        end

(* Calculates the entropy of an input char list *)
fun entropy_calculation ([]:char list) = 0.0
    | entropy_calculation (x:char list) =
        let
            val input = x;
            val frequencies= [0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228, 0.02015, 0.06094, 0.06966, 0.00153, 0.00772, 0.04025, 0.02406, 0.06749, 0.07507, 0.01929, 0.00095, 0.05987, 0.06327, 0.09056, 0.02758, 0.00978, 0.02360, 0.00150, 0.01974, 0.00074]
            val char_frequencies = List.tabulate(26, fn y => char_count(input, y)  )
            fun  multiply_lists (head::tail,hea::tai) = ((head)*(Math.ln (hea))+(multiply_lists (tail, tai)))
            | multiply_lists (_,_) = 0.0
        in
            ~(multiply_lists(char_frequencies,frequencies))
        end

(*Calculates the position of minimum real in an array*)
fun getpos_min_value ([]:real list) = 0
    | getpos_min_value [x] = 0
    | getpos_min_value ((h::t)) =
        let
            fun minimum_element [] = 0.0
                | minimum_element [x] = x
                | minimum_element (x::t) = Real.min(x,minimum_element t)
        in
            if h<(minimum_element t) then 0 else 1+getpos_min_value t
        end

(*Tranposes an inpit char list by n letters | Perfors ROTN*)
fun transpose_string ([],n) = []
    | transpose_string (head::tail,n) =
        let
            val head_transposed =
            if Char.isAlpha head then
                if ((Char.ord (Char.toUpper head))-n) < Char.ord #"A" then
                    Char.chr ((Char.ord head)-n+26)
                else
                    Char.chr ((Char.ord head)-n)
            else head
        in
            (head_transposed::transpose_string (tail,n))
        end

(*Main solve function*)
fun solve encrypted =
    let
        val final_offset = getpos_min_value (List.tabulate (26,fn y => (entropy_calculation (transpose_string (encrypted,y)))))
    in
        transpose_string (encrypted,final_offset)
    end

(*Interpreter call function*)
fun decrypt infile = TextIO.print (String.implode ((solve (String.explode (TextIO.inputAll (TextIO.openIn infile))))))
(*fun decrypt infile = solve (String.explode (TextIO.inputAll (TextIO.openIn infile)))*)

(* openIN returns an input stream and openAll creates a vector from that stream,
 an array of chars, which solve() expects as an input*)

 fun  multiply_lists (head::tail,hea::tai) = ((head)*(Math.ln (hea))+(multiply_lists (tail, tai)))
 | multiply_lists (_,_) = 0.0
(*
 ((entropy_calculation (transope_string (encrypted,0)))::
  (entropy_calculation (transope_string (encrypted,1)))::
  (entropy_calculation (transope_string (encrypted,2)))::
  (entropy_calculation (transope_string (encrypted,3)))::
  (entropy_calculation (transope_string (encrypted,4)))::
  (entropy_calculation (transope_string (encrypted,5)))::
  (entropy_calculation (transope_string (encrypted,6)))::
  (entropy_calculation (transope_string (encrypted,7)))::
  (entropy_calculation (transope_string (encrypted,8)))::
  (entropy_calculation (transope_string (encrypted,9)))::
  (entropy_calculation (transope_string (encrypted,10)))::
  (entropy_calculation (transope_string (encrypted,11)))::
  (entropy_calculation (transope_string (encrypted,12)))::
  (entropy_calculation (transope_string (encrypted,13)))::
  (entropy_calculation (transope_string (encrypted,14)))::
  (entropy_calculation (transope_string (encrypted,15)))::
  (entropy_calculation (transope_string (encrypted,16)))::
  (entropy_calculation (transope_string (encrypted,17)))::
  (entropy_calculation (transope_string (encrypted,18)))::
  (entropy_calculation (transope_string (encrypted,19)))::
  (entropy_calculation (transope_string (encrypted,20)))::
  (entropy_calculation (transope_string (encrypted,21)))::
  (entropy_calculation (transope_string (encrypted,22)))::
  (entropy_calculation (transope_string (encrypted,23)))::
  (entropy_calculation (transope_string (encrypted,24)))::
  (entropy_calculation (transope_string (encrypted,25))))
  *)
