
# our 'm' is a prime number, so the modular inverse is 
# known to be n^(m-2) (Euler Theorem)
# https://en.wikipedia.org/wiki/Modular_multiplicative_inverse#Using_Euler.27s_theorem
function modInv($n, $m)
{
    return [System.Numerics.BigInteger]::ModPow($n, $m - 2, $m)
}

function pow($a, $b, $m)
{ 
    return [System.Numerics.BigInteger]::ModPow($a, $b, $m)
}

function deal($decksize, $pos)
{
    return $deckSize - 1 - $pos
}

function revDeal($decksize, $pos)
{
    return $deckSize - 1 - $pos
}

function cut($decksize, $pos, $n)
{
    return ($pos + $decksize - $n) % $decksize
}

function revCut($decksize, $pos, $n)
{
    return ($pos + $decksize + $n) % $decksize
}

function inc($decksize, $pos, $n)
{
    return ($n * $pos) % $decksize
}

function revInc($decksize, $pos, $n)
{
    return ((modInv -n $n -m $decksize) * $pos) % $decksize
}

function calcF($decksize, $pos, $datalines)
{
    foreach ($line in $datalines)
    {
        $type = $line[0]
        
        $val = [Int]::Parse($line.Remove(0, 1))

        if ($type -eq 'N')
        {
            $pos = (deal -decksize $decksize -pos $pos)
        }

        elseif ($type -eq 'I')
        {
            $pos = (inc -decksize $decksize -pos $pos -n $val)
        }

        elseif ($type -eq 'C')
        {
            $pos = (cut -decksize $decksize -pos $pos -n $val)
        }

        else 
        {
            write-error "INVALID"
        }
    }
    return $pos
}

function calcFInv($decksize, $pos, $datalines)
{
    foreach ($line in $datalines)
    {
        $type = $line[0]
        
        $val = [Int]::Parse($line.Remove(0, 1))

        if ($type -eq 'N')
        {
            $pos = (revDeal -decksize $decksize -pos $pos)
        }

        if ($type -eq 'I')
        {
            $pos = (revInc -decksize $decksize -pos $pos -n $val)
        }

        if ($type -eq 'C')
        {
            $pos = (revCut -decksize $decksize -pos $pos -n $val)
        }
    }
    return $pos
}


function readInput($file, [switch] $reverseTime)
{
    [string[]] $fileLines = Get-Content $file
    if ($reverseTime)
    {
        [array]::Reverse($fileLines)
    }

    return $fileLines
}

function solvePart2()
{
    $file = "C:\aoc-2019\AocSolutions\days\22\input.txt"

    # we go backwards in time
    $pos = 2020
    $datalines  = readInput $file -reverseTime
    $decksize   = 119315717514047
    $iterations = 101741582076661

    # calcFInv calculated the F function, for a given POS when going backwards in time
    $fOne    = calcFInv -decksize $decksize -pos $pos    -datalines $datalines
    $fTwo    = calcFInv -decksize $decksize -pos $fOne   -datalines $datalines
    $fThree  = calcFInv -decksize $decksize -pos $fTwo   -datalines $datalines
    $fFour   = calcFInv -decksize $decksize -pos $fThree -datalines $datalines

    # revInc, revCut, revDeal are all linear functions (mx + n), so f(g(h(pos))) is also linear
    # proceed to determine our M and N
    $m = ($fOne - $fTwo) * (modInv -n ($pos - $fOne + $decksize) -m $decksize) % $decksize
    $n = ($fOne - $m * $pos) % $decksize

    # test our findings
    $test1 = ($m * $pos + $n)   % $decksize
    $test2 = ($m * $test1 + $n) % $decksize
    $test3 = ($m * $test2 + $n) % $decksize
    $test4 = ($m * $test3 + $n) % $decksize

    if ( ($test1 -ne $fOne) -or ($test2 -ne $fTwo) -or ($test3 -ne $fThree) -or ($test4 -ne $fFour)) 
    {
        Write-Error "tests failed"
    }

    # go way back in time, by expansing the power series, f(f(f(f(f(f(f(f... iterations times
    $pp = (pow -a $m -b ($iterations) -m $decksize)
    $modinv = (modInv -n ($m - 1) -m $decksize)
    $term1 = ($pp - 1) * $modInv * $n

    $answer = ($pp * $pos + $term1) % $decksize

    Write-Output ($answer + $decksize)
}

solvePart2