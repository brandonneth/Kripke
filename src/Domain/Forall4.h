//AUTOGENERATED BY genForallN.py
  
#ifndef __DOMAIN_FORALL4_H__
#define __DOMAIN_FORALL4_H__

#include<RAJA/RAJA.hxx>



/******************************************************************
 *  Policy base class, forall4()
 ******************************************************************/

    template<typename LOOP_ORDER, typename POL_I, typename POL_J, typename POL_K, typename POL_L>
    struct ForallPolicy4 {
      typedef LOOP_ORDER LoopOrder;
      typedef POL_I PolicyI;
      typedef POL_J PolicyJ;
      typedef POL_K PolicyK;
      typedef POL_L PolicyL;
    };


/******************************************************************
 *  Default Executor for forall4()
 ******************************************************************/

    template<typename POLICY_I, typename POLICY_J, typename POLICY_K, typename POLICY_L, typename TI, typename TJ, typename TK, typename TL>
    class Forall4Executor {
      public:  
        template<typename BODY>
        inline void operator()(TI const &is_i, TJ const &is_j, TK const &is_k, TL const &is_l, BODY const &body) const {
          RAJA::forall<POLICY_I>(is_i, RAJA_LAMBDA(int i){
            exec(is_j, is_k, is_l, RAJA_LAMBDA(int j, int k, int l){
              body(i, j, k, l);
            });
          });
        }

      private:
        Forall3Executor<POLICY_J, POLICY_K, POLICY_L, TJ, TK, TL> exec;
    };


/******************************************************************
 *  Permutations layer for forall4()
 ******************************************************************/

      template<typename POLICY, typename TI, typename TJ, typename TK, typename TL, typename BODY>
      RAJA_INLINE void forall4_permute(PERM_IJKL, TI const &is_i, TJ const &is_j, TK const &is_k, TL const &is_l, BODY const &body){
        Forall4Executor<typename POLICY::PolicyI, typename POLICY::PolicyJ, typename POLICY::PolicyK, typename POLICY::PolicyL, TI, TJ, TK, TL> const exec;
        exec(is_i, is_j, is_k, is_l, RAJA_LAMBDA(int i, int j, int k, int l){
          body(i, j, k, l);
        });
      }

      template<typename POLICY, typename TI, typename TJ, typename TK, typename TL, typename BODY>
      RAJA_INLINE void forall4_permute(PERM_IJLK, TI const &is_i, TJ const &is_j, TK const &is_k, TL const &is_l, BODY const &body){
        Forall4Executor<typename POLICY::PolicyI, typename POLICY::PolicyJ, typename POLICY::PolicyL, typename POLICY::PolicyK, TI, TJ, TL, TK> const exec;
        exec(is_i, is_j, is_l, is_k, RAJA_LAMBDA(int i, int j, int l, int k){
          body(i, j, k, l);
        });
      }

      template<typename POLICY, typename TI, typename TJ, typename TK, typename TL, typename BODY>
      RAJA_INLINE void forall4_permute(PERM_IKJL, TI const &is_i, TJ const &is_j, TK const &is_k, TL const &is_l, BODY const &body){
        Forall4Executor<typename POLICY::PolicyI, typename POLICY::PolicyK, typename POLICY::PolicyJ, typename POLICY::PolicyL, TI, TK, TJ, TL> const exec;
        exec(is_i, is_k, is_j, is_l, RAJA_LAMBDA(int i, int k, int j, int l){
          body(i, j, k, l);
        });
      }

      template<typename POLICY, typename TI, typename TJ, typename TK, typename TL, typename BODY>
      RAJA_INLINE void forall4_permute(PERM_IKLJ, TI const &is_i, TJ const &is_j, TK const &is_k, TL const &is_l, BODY const &body){
        Forall4Executor<typename POLICY::PolicyI, typename POLICY::PolicyK, typename POLICY::PolicyL, typename POLICY::PolicyJ, TI, TK, TL, TJ> const exec;
        exec(is_i, is_k, is_l, is_j, RAJA_LAMBDA(int i, int k, int l, int j){
          body(i, j, k, l);
        });
      }

      template<typename POLICY, typename TI, typename TJ, typename TK, typename TL, typename BODY>
      RAJA_INLINE void forall4_permute(PERM_ILJK, TI const &is_i, TJ const &is_j, TK const &is_k, TL const &is_l, BODY const &body){
        Forall4Executor<typename POLICY::PolicyI, typename POLICY::PolicyL, typename POLICY::PolicyJ, typename POLICY::PolicyK, TI, TL, TJ, TK> const exec;
        exec(is_i, is_l, is_j, is_k, RAJA_LAMBDA(int i, int l, int j, int k){
          body(i, j, k, l);
        });
      }

      template<typename POLICY, typename TI, typename TJ, typename TK, typename TL, typename BODY>
      RAJA_INLINE void forall4_permute(PERM_ILKJ, TI const &is_i, TJ const &is_j, TK const &is_k, TL const &is_l, BODY const &body){
        Forall4Executor<typename POLICY::PolicyI, typename POLICY::PolicyL, typename POLICY::PolicyK, typename POLICY::PolicyJ, TI, TL, TK, TJ> const exec;
        exec(is_i, is_l, is_k, is_j, RAJA_LAMBDA(int i, int l, int k, int j){
          body(i, j, k, l);
        });
      }

      template<typename POLICY, typename TI, typename TJ, typename TK, typename TL, typename BODY>
      RAJA_INLINE void forall4_permute(PERM_JIKL, TI const &is_i, TJ const &is_j, TK const &is_k, TL const &is_l, BODY const &body){
        Forall4Executor<typename POLICY::PolicyJ, typename POLICY::PolicyI, typename POLICY::PolicyK, typename POLICY::PolicyL, TJ, TI, TK, TL> const exec;
        exec(is_j, is_i, is_k, is_l, RAJA_LAMBDA(int j, int i, int k, int l){
          body(i, j, k, l);
        });
      }

      template<typename POLICY, typename TI, typename TJ, typename TK, typename TL, typename BODY>
      RAJA_INLINE void forall4_permute(PERM_JILK, TI const &is_i, TJ const &is_j, TK const &is_k, TL const &is_l, BODY const &body){
        Forall4Executor<typename POLICY::PolicyJ, typename POLICY::PolicyI, typename POLICY::PolicyL, typename POLICY::PolicyK, TJ, TI, TL, TK> const exec;
        exec(is_j, is_i, is_l, is_k, RAJA_LAMBDA(int j, int i, int l, int k){
          body(i, j, k, l);
        });
      }

      template<typename POLICY, typename TI, typename TJ, typename TK, typename TL, typename BODY>
      RAJA_INLINE void forall4_permute(PERM_JKIL, TI const &is_i, TJ const &is_j, TK const &is_k, TL const &is_l, BODY const &body){
        Forall4Executor<typename POLICY::PolicyJ, typename POLICY::PolicyK, typename POLICY::PolicyI, typename POLICY::PolicyL, TJ, TK, TI, TL> const exec;
        exec(is_j, is_k, is_i, is_l, RAJA_LAMBDA(int j, int k, int i, int l){
          body(i, j, k, l);
        });
      }

      template<typename POLICY, typename TI, typename TJ, typename TK, typename TL, typename BODY>
      RAJA_INLINE void forall4_permute(PERM_JKLI, TI const &is_i, TJ const &is_j, TK const &is_k, TL const &is_l, BODY const &body){
        Forall4Executor<typename POLICY::PolicyJ, typename POLICY::PolicyK, typename POLICY::PolicyL, typename POLICY::PolicyI, TJ, TK, TL, TI> const exec;
        exec(is_j, is_k, is_l, is_i, RAJA_LAMBDA(int j, int k, int l, int i){
          body(i, j, k, l);
        });
      }

      template<typename POLICY, typename TI, typename TJ, typename TK, typename TL, typename BODY>
      RAJA_INLINE void forall4_permute(PERM_JLIK, TI const &is_i, TJ const &is_j, TK const &is_k, TL const &is_l, BODY const &body){
        Forall4Executor<typename POLICY::PolicyJ, typename POLICY::PolicyL, typename POLICY::PolicyI, typename POLICY::PolicyK, TJ, TL, TI, TK> const exec;
        exec(is_j, is_l, is_i, is_k, RAJA_LAMBDA(int j, int l, int i, int k){
          body(i, j, k, l);
        });
      }

      template<typename POLICY, typename TI, typename TJ, typename TK, typename TL, typename BODY>
      RAJA_INLINE void forall4_permute(PERM_JLKI, TI const &is_i, TJ const &is_j, TK const &is_k, TL const &is_l, BODY const &body){
        Forall4Executor<typename POLICY::PolicyJ, typename POLICY::PolicyL, typename POLICY::PolicyK, typename POLICY::PolicyI, TJ, TL, TK, TI> const exec;
        exec(is_j, is_l, is_k, is_i, RAJA_LAMBDA(int j, int l, int k, int i){
          body(i, j, k, l);
        });
      }

      template<typename POLICY, typename TI, typename TJ, typename TK, typename TL, typename BODY>
      RAJA_INLINE void forall4_permute(PERM_KIJL, TI const &is_i, TJ const &is_j, TK const &is_k, TL const &is_l, BODY const &body){
        Forall4Executor<typename POLICY::PolicyK, typename POLICY::PolicyI, typename POLICY::PolicyJ, typename POLICY::PolicyL, TK, TI, TJ, TL> const exec;
        exec(is_k, is_i, is_j, is_l, RAJA_LAMBDA(int k, int i, int j, int l){
          body(i, j, k, l);
        });
      }

      template<typename POLICY, typename TI, typename TJ, typename TK, typename TL, typename BODY>
      RAJA_INLINE void forall4_permute(PERM_KILJ, TI const &is_i, TJ const &is_j, TK const &is_k, TL const &is_l, BODY const &body){
        Forall4Executor<typename POLICY::PolicyK, typename POLICY::PolicyI, typename POLICY::PolicyL, typename POLICY::PolicyJ, TK, TI, TL, TJ> const exec;
        exec(is_k, is_i, is_l, is_j, RAJA_LAMBDA(int k, int i, int l, int j){
          body(i, j, k, l);
        });
      }

      template<typename POLICY, typename TI, typename TJ, typename TK, typename TL, typename BODY>
      RAJA_INLINE void forall4_permute(PERM_KJIL, TI const &is_i, TJ const &is_j, TK const &is_k, TL const &is_l, BODY const &body){
        Forall4Executor<typename POLICY::PolicyK, typename POLICY::PolicyJ, typename POLICY::PolicyI, typename POLICY::PolicyL, TK, TJ, TI, TL> const exec;
        exec(is_k, is_j, is_i, is_l, RAJA_LAMBDA(int k, int j, int i, int l){
          body(i, j, k, l);
        });
      }

      template<typename POLICY, typename TI, typename TJ, typename TK, typename TL, typename BODY>
      RAJA_INLINE void forall4_permute(PERM_KJLI, TI const &is_i, TJ const &is_j, TK const &is_k, TL const &is_l, BODY const &body){
        Forall4Executor<typename POLICY::PolicyK, typename POLICY::PolicyJ, typename POLICY::PolicyL, typename POLICY::PolicyI, TK, TJ, TL, TI> const exec;
        exec(is_k, is_j, is_l, is_i, RAJA_LAMBDA(int k, int j, int l, int i){
          body(i, j, k, l);
        });
      }

      template<typename POLICY, typename TI, typename TJ, typename TK, typename TL, typename BODY>
      RAJA_INLINE void forall4_permute(PERM_KLIJ, TI const &is_i, TJ const &is_j, TK const &is_k, TL const &is_l, BODY const &body){
        Forall4Executor<typename POLICY::PolicyK, typename POLICY::PolicyL, typename POLICY::PolicyI, typename POLICY::PolicyJ, TK, TL, TI, TJ> const exec;
        exec(is_k, is_l, is_i, is_j, RAJA_LAMBDA(int k, int l, int i, int j){
          body(i, j, k, l);
        });
      }

      template<typename POLICY, typename TI, typename TJ, typename TK, typename TL, typename BODY>
      RAJA_INLINE void forall4_permute(PERM_KLJI, TI const &is_i, TJ const &is_j, TK const &is_k, TL const &is_l, BODY const &body){
        Forall4Executor<typename POLICY::PolicyK, typename POLICY::PolicyL, typename POLICY::PolicyJ, typename POLICY::PolicyI, TK, TL, TJ, TI> const exec;
        exec(is_k, is_l, is_j, is_i, RAJA_LAMBDA(int k, int l, int j, int i){
          body(i, j, k, l);
        });
      }

      template<typename POLICY, typename TI, typename TJ, typename TK, typename TL, typename BODY>
      RAJA_INLINE void forall4_permute(PERM_LIJK, TI const &is_i, TJ const &is_j, TK const &is_k, TL const &is_l, BODY const &body){
        Forall4Executor<typename POLICY::PolicyL, typename POLICY::PolicyI, typename POLICY::PolicyJ, typename POLICY::PolicyK, TL, TI, TJ, TK> const exec;
        exec(is_l, is_i, is_j, is_k, RAJA_LAMBDA(int l, int i, int j, int k){
          body(i, j, k, l);
        });
      }

      template<typename POLICY, typename TI, typename TJ, typename TK, typename TL, typename BODY>
      RAJA_INLINE void forall4_permute(PERM_LIKJ, TI const &is_i, TJ const &is_j, TK const &is_k, TL const &is_l, BODY const &body){
        Forall4Executor<typename POLICY::PolicyL, typename POLICY::PolicyI, typename POLICY::PolicyK, typename POLICY::PolicyJ, TL, TI, TK, TJ> const exec;
        exec(is_l, is_i, is_k, is_j, RAJA_LAMBDA(int l, int i, int k, int j){
          body(i, j, k, l);
        });
      }

      template<typename POLICY, typename TI, typename TJ, typename TK, typename TL, typename BODY>
      RAJA_INLINE void forall4_permute(PERM_LJIK, TI const &is_i, TJ const &is_j, TK const &is_k, TL const &is_l, BODY const &body){
        Forall4Executor<typename POLICY::PolicyL, typename POLICY::PolicyJ, typename POLICY::PolicyI, typename POLICY::PolicyK, TL, TJ, TI, TK> const exec;
        exec(is_l, is_j, is_i, is_k, RAJA_LAMBDA(int l, int j, int i, int k){
          body(i, j, k, l);
        });
      }

      template<typename POLICY, typename TI, typename TJ, typename TK, typename TL, typename BODY>
      RAJA_INLINE void forall4_permute(PERM_LJKI, TI const &is_i, TJ const &is_j, TK const &is_k, TL const &is_l, BODY const &body){
        Forall4Executor<typename POLICY::PolicyL, typename POLICY::PolicyJ, typename POLICY::PolicyK, typename POLICY::PolicyI, TL, TJ, TK, TI> const exec;
        exec(is_l, is_j, is_k, is_i, RAJA_LAMBDA(int l, int j, int k, int i){
          body(i, j, k, l);
        });
      }

      template<typename POLICY, typename TI, typename TJ, typename TK, typename TL, typename BODY>
      RAJA_INLINE void forall4_permute(PERM_LKIJ, TI const &is_i, TJ const &is_j, TK const &is_k, TL const &is_l, BODY const &body){
        Forall4Executor<typename POLICY::PolicyL, typename POLICY::PolicyK, typename POLICY::PolicyI, typename POLICY::PolicyJ, TL, TK, TI, TJ> const exec;
        exec(is_l, is_k, is_i, is_j, RAJA_LAMBDA(int l, int k, int i, int j){
          body(i, j, k, l);
        });
      }

      template<typename POLICY, typename TI, typename TJ, typename TK, typename TL, typename BODY>
      RAJA_INLINE void forall4_permute(PERM_LKJI, TI const &is_i, TJ const &is_j, TK const &is_k, TL const &is_l, BODY const &body){
        Forall4Executor<typename POLICY::PolicyL, typename POLICY::PolicyK, typename POLICY::PolicyJ, typename POLICY::PolicyI, TL, TK, TJ, TI> const exec;
        exec(is_l, is_k, is_j, is_i, RAJA_LAMBDA(int l, int k, int j, int i){
          body(i, j, k, l);
        });
      }


/******************************************************************
 *  User interface, forall4()
 ******************************************************************/

    template<typename POLICY, typename TI, typename TJ, typename TK, typename TL, typename BODY>
    RAJA_INLINE void forall4(TI const &is_i, TJ const &is_j, TK const &is_k, TL const &is_l, BODY const &body){
      typedef typename POLICY::LoopOrder L;
      forall4_permute<POLICY, TI, TJ, TK, TL, BODY>(L(), is_i, is_j, is_k, is_l, body);
    }


  
#endif

