//AUTOGENERATED BY genForallN.py
  
#ifndef __DOMAIN_FORALL2_H__
#define __DOMAIN_FORALL2_H__

#include<RAJA/RAJA.hxx>


    template<typename LOOP_NEST, typename LOOP_ORDER, typename POL_I, typename POL_J>
    struct ForallPolicy2 {
      typedef LOOP_NEST LoopNesting;
      typedef LOOP_ORDER LoopOrder;      
      typedef POL_I PolicyI;
      typedef POL_J PolicyJ;
    };
    /******************************************************************
     *  Default Executor for forall2()
     ******************************************************************/

        template<typename POLICY_I, typename POLICY_J, typename TI, typename TJ>
        class Forall2Executor {
          public:
            template<typename BODY>
            inline void operator()(TI const &is_i, TJ const &is_j, BODY const &body) const {
              RAJA::forall<POLICY_I>(is_i, RAJA_LAMBDA(int i){
                RAJA::forall<POLICY_J>(is_j, RAJA_LAMBDA(int j){
                  body(i, j);
                });
              });
            }
        };

/******************************************************************
 *  Executors for forall2()
 ******************************************************************/
/*
  // Default executor
  template<typename POLICYI, typename POLICYJ, typename TI, typename TJ>
  class Forall2Executor{
    public:

      // Default executor uses nested RAJA::forall's
      template<typename BODY>
      inline void operator()(TI const &is_i, TJ const &is_j, BODY const &body) const {
        RAJA::forall<POLICYI>(is_i, RAJA_LAMBDA(int i){
          RAJA::forall<POLICYJ>(is_j, RAJA_LAMBDA(int j){
            body(i, j);
          });
        });
      }
  };
*/

        /*
  // Default executor
  template<typename POLICYI, typename POLICYJ, typename POLICYK, typename TI, typename TJ, typename TK>
  class Forall3Executor{
    public:

      // Default executor peels off outer loop with RAJA::forall, passes inner loops
      // to Forall2 executor

      template<typename BODY>
      inline void operator()(TI const &is_i, TJ const &is_j, TK const &is_k, BODY const &body) const {
        RAJA::forall<POLICYI>(is_i, RAJA_LAMBDA(int i){
          exec(is_j, is_k, RAJA_LAMBDA(int j, int k){
            body(i, j, k);
          });
        });
      }
    private:
      Forall2Executor<POLICYJ, POLICYK, TJ, TK> exec;
  };*/

#ifdef _OPENMP
  /** Executor with OpenMP collapse(2)
   *
   * Auto-detects when:
   *   -- omp_parallel_for_exec is used for top 2 index sets
   *   -- RangeSegment is used for top 2 index sets
   */
  template<>
  class Forall2Executor<RAJA::omp_parallel_for_exec, RAJA::omp_parallel_for_exec, RAJA::RangeSegment, RAJA::RangeSegment>{
    public:

      // Default executor uses nested RAJA::forall's
      template<typename BODY>
      inline void operator()(RAJA::RangeSegment const &is_i, RAJA::RangeSegment const &is_j, BODY const &body) const {
        printf("collapse(2)\n\n");
        int const i_start = is_i.getBegin();
        int const i_end   = is_i.getEnd();

        int const j_start = is_j.getBegin();
        int const j_end   = is_j.getEnd();

#pragma omp parallel for collapse(2)
        for(int i = i_start;i < i_end;++ i){
          for(int j = j_start;j < j_end;++ j){
            body(i, j);
          }
        }
      }
  };
#endif



/******************************************************************
 *  Permutations for forall2()
 ******************************************************************/
  template<typename POLICY, typename TI, typename TJ, typename BODY>
   RAJA_INLINE void forall2_permute(PERM_IJ, TI const &is_i, TJ const &is_j, BODY const &body){
     Forall2Executor<typename POLICY::PolicyI, typename POLICY::PolicyJ, TI, TJ> const exec;
     exec(is_i, is_j, RAJA_LAMBDA(int i, int j){
       body(i, j);
     });
   }

   template<typename POLICY, typename TI, typename TJ, typename BODY>
   RAJA_INLINE void forall2_permute(PERM_JI, TI const &is_i, TJ const &is_j, BODY const &body){
     Forall2Executor<typename POLICY::PolicyJ, typename POLICY::PolicyI, TJ, TI> const exec;
     exec(is_j, is_i, RAJA_LAMBDA(int j, int i){
       body(i, j);
     });
   }


/******************************************************************
 *  User interface for forall2()
 ******************************************************************/


    template<typename POLICY, typename TI, typename TJ, typename BODY>
        RAJA_INLINE void forall2(TI const &is_i, TJ const &is_j, BODY const &body){
          typedef typename POLICY::LoopOrder L;
          forall2_permute<POLICY, TI, TJ, BODY>(L(), is_i, is_j, body);
        }

  
#endif

