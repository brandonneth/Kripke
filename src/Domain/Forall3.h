//AUTOGENERATED BY genForallN.py
  
#ifndef __DOMAIN_FORALL3_H__
#define __DOMAIN_FORALL3_H__

#include<RAJA/RAJA.hxx>



/******************************************************************
 *  Policy base class, forall3()
 ******************************************************************/

    template<typename LOOP_ORDER, typename POL_I, typename POL_J, typename POL_K>
    struct ForallPolicy3 {
      typedef LOOP_ORDER LoopOrder;
      typedef POL_I PolicyI;
      typedef POL_J PolicyJ;
      typedef POL_K PolicyK;
    };


/******************************************************************
 *  Default Executor for forall3()
 ******************************************************************/

    template<typename POLICY_I, typename POLICY_J, typename POLICY_K, typename TI, typename TJ, typename TK>
    class Forall3Executor {
      public:  
        template<typename BODY>
        inline void operator()(TI const &is_i, TJ const &is_j, TK const &is_k, BODY const &body) const {
          RAJA::forall<POLICY_I>(is_i, RAJA_LAMBDA(int i){
            exec(is_j, is_k, RAJA_LAMBDA(int j, int k){
              body(i, j, k);
            });
          });
        }

      private:
        Forall2Executor<POLICY_J, POLICY_K, TJ, TK> exec;
    };


/******************************************************************
 *  Permutations layer for forall3()
 ******************************************************************/

      template<typename POLICY, typename TI, typename TJ, typename TK, typename BODY>
      RAJA_INLINE void forall3_permute(PERM_IJK, TI const &is_i, TJ const &is_j, TK const &is_k, BODY const &body){
        Forall3Executor<typename POLICY::PolicyI, typename POLICY::PolicyJ, typename POLICY::PolicyK, TI, TJ, TK> const exec;
        exec(is_i, is_j, is_k, RAJA_LAMBDA(int i, int j, int k){
          body(i, j, k);
        });
      }

      template<typename POLICY, typename TI, typename TJ, typename TK, typename BODY>
      RAJA_INLINE void forall3_permute(PERM_IKJ, TI const &is_i, TJ const &is_j, TK const &is_k, BODY const &body){
        Forall3Executor<typename POLICY::PolicyI, typename POLICY::PolicyK, typename POLICY::PolicyJ, TI, TK, TJ> const exec;
        exec(is_i, is_k, is_j, RAJA_LAMBDA(int i, int k, int j){
          body(i, j, k);
        });
      }

      template<typename POLICY, typename TI, typename TJ, typename TK, typename BODY>
      RAJA_INLINE void forall3_permute(PERM_JIK, TI const &is_i, TJ const &is_j, TK const &is_k, BODY const &body){
        Forall3Executor<typename POLICY::PolicyJ, typename POLICY::PolicyI, typename POLICY::PolicyK, TJ, TI, TK> const exec;
        exec(is_j, is_i, is_k, RAJA_LAMBDA(int j, int i, int k){
          body(i, j, k);
        });
      }

      template<typename POLICY, typename TI, typename TJ, typename TK, typename BODY>
      RAJA_INLINE void forall3_permute(PERM_JKI, TI const &is_i, TJ const &is_j, TK const &is_k, BODY const &body){
        Forall3Executor<typename POLICY::PolicyJ, typename POLICY::PolicyK, typename POLICY::PolicyI, TJ, TK, TI> const exec;
        exec(is_j, is_k, is_i, RAJA_LAMBDA(int j, int k, int i){
          body(i, j, k);
        });
      }

      template<typename POLICY, typename TI, typename TJ, typename TK, typename BODY>
      RAJA_INLINE void forall3_permute(PERM_KIJ, TI const &is_i, TJ const &is_j, TK const &is_k, BODY const &body){
        Forall3Executor<typename POLICY::PolicyK, typename POLICY::PolicyI, typename POLICY::PolicyJ, TK, TI, TJ> const exec;
        exec(is_k, is_i, is_j, RAJA_LAMBDA(int k, int i, int j){
          body(i, j, k);
        });
      }

      template<typename POLICY, typename TI, typename TJ, typename TK, typename BODY>
      RAJA_INLINE void forall3_permute(PERM_KJI, TI const &is_i, TJ const &is_j, TK const &is_k, BODY const &body){
        Forall3Executor<typename POLICY::PolicyK, typename POLICY::PolicyJ, typename POLICY::PolicyI, TK, TJ, TI> const exec;
        exec(is_k, is_j, is_i, RAJA_LAMBDA(int k, int j, int i){
          body(i, j, k);
        });
      }


/******************************************************************
 *  User interface, forall3()
 ******************************************************************/

    template<typename POLICY, typename TI, typename TJ, typename TK, typename BODY>
    RAJA_INLINE void forall3(TI const &is_i, TJ const &is_j, TK const &is_k, BODY const &body){
      typedef typename POLICY::LoopOrder L;
      forall3_permute<POLICY, TI, TJ, TK, BODY>(L(), is_i, is_j, is_k, body);
    }


  
#endif

