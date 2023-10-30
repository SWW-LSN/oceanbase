#define USING_LOG_PREFIX SQL_ENG
#include "sql/engine/expr/ob_expr_hello.h"
#include "sql/engine/expr/ob_expr_util.h"
#include "share/object/ob_obj_cast.h"
#include "objit/common/ob_item_type.h"
#include "sql/session/ob_sql_session_info.h"
#include "sql/engine/ob_physical_plan_ctx.h"
#include "lib/mysqlclient/ob_mysql_result.h"
#include "lib/mysqlclient/ob_mysql_transaction.h"
#include "lib/string/ob_sql_string.h"
#include "lib/mysqlclient/ob_mysql_proxy.h"
#include "lib/oblog/ob_log_module.h"
#include "sql/engine/ob_exec_context.h"
#include "sql/engine/expr/ob_expr_operator.h"
#include "lib/oblog/ob_log.h"
#include "sql/engine/expr/ob_datum_cast.h"
#include "sql/engine/expr/ob_expr_lob_utils.h"


using namespace oceanbase::common;
using namespace oceanbase::sql;

namespace oceanbase {
namespace sql {

////////////////////////////////////////////////////////////////
const char ObExprHello::hello_str[] = "Hello, OceanBase Competition!";
const int64_t ObExprHello::str_len = sizeof(hello_str) - 1;


int ObExprHello::eval(const ObExpr& expr, ObEvalCtx &ctx, ObDatum& expr_datum)
{
  int ret = OB_SUCCESS;
  UNUSED(expr);
  const ObBasicSessionInfo *session_info = NULL;
  if (OB_ISNULL(session_info = ctx.exec_ctx_.get_my_session())) {
    ret = OB_ERR_UNEXPECTED;
  } else {
    expr_datum.set_string(hello_str, sizeof(hello_str) - 1);
  }
  return ret;
}

ObExprHello::ObExprHello(common::ObIAllocator& alloc)
    :ObStringExprOperator(alloc, T_FUN_SYS_HELLO, N_HELLO, 0, NOT_VALID_FOR_GENERATED_COL)
{
}

int ObExprHello::cg_expr(ObExprCGCtx& op_cg_ctx, const ObRawExpr& raw_expr, ObExpr& rt_expr) const
{
  UNUSED(raw_expr);
  UNUSED(op_cg_ctx);
  rt_expr.eval_func_ = ObExprHello::eval;
  return OB_SUCCESS;
}




int ObExprHello::calc_result_type0(ObExprResType& res_type, ObExprTypeCtx& type_ctx) const
{
  int ret = OB_SUCCESS;
  UNUSED(type_ctx);

  res_type.set_varchar();
  res_type.set_default_collation_type();
  res_type.set_collation_level(CS_LEVEL_SYSCONST);
  res_type.set_length(static_cast<ObLength>(str_len));
  return ret;
}

}  // namespace sql
}  // namespace oceanbase