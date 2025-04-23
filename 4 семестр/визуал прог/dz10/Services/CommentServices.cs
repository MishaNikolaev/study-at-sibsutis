using dz10.Model;
using dz10.Repository;
using WebApplication2.Repositories;

namespace dz10.Services
{
    public class CommentService : ICommentServices
    {
        private readonly ICommentRepository _commentRepository;

        public CommentService(ICommentRepository commentRepository)
        {
            _commentRepository = commentRepository;
        }

        public IEnumerable<Comment> GetAllComments() => _commentRepository.GetAll();

        public Comment? GetCommentById(int id) => _commentRepository.GetById(id);

        public Comment AddComment(Comment comment) => _commentRepository.Add(comment);

        public Comment? UpdateComment(int id, Comment comment) => _commentRepository.Update(id, comment);

        public bool DeleteComment(int id) => _commentRepository.Delete(id);
    }
}