# Building_puzzle

"概要"  
  ルールは以下を参照してください。  
   https://www.conceptispuzzles.com/ja/index.aspx?uri=puzzle/skyscrapers/rules  

  このコードは42Tokyoの入学試験であるpiscineの時に書いたものを復習がてら何も見ずに書き直したものです。（この文言は必要ないかもw)

  現在プログラムは計算回数の設計上、6 * 6　マス以上の部いるビルディングパズルについてはTime Outしてしまうので、改良が必要。

  5 * 5マスまでの解は求められる。

  マスの大きさを変えたい場合はmain.cの'#define SIZE 4'となってる箇所の4の部分を他の数字にすれば良い。ただ、機能上4か５に対しての解決策となりそう。

"Test_case" (Example)  

  '4 * 4'  
  ./Building "4 3 2 1 1 2 2 2 4 3 2 1 1 2 2 2"  
  
  ↓  

  1 2 3 4  
  2 3 4 1  
  3 4 1 2  
  4 1 2 3  
  

  '5 * 5'  
  ./Building "2 1 3 3 2 3 5 2 1 3 2 1 2 3 3 2 5 1 3 2"  

  ↓  

  2 5 1 3 4  
  5 4 3 2 1  
  4 3 2 1 5  
  1 2 5 4 3  
  3 1 4 5 2  

"使用アルゴリズム"  

  バックトラッキング法  
